#include "Sevensegment.hpp"

#include <catch2/catch_test_macros.hpp>

#include <sstream>

TEST_CASE("testLargeDigitZero")
{
  std::ostringstream output{};
  printLargeDigit(0, output);
  REQUIRE(output.str() == " - \n"
                          "| |\n"
                          "   \n"
                          "| |\n"
                          " - \n");
}

static const std::array<std::array<std::string, 5>, 10> DIGITS_EXPECT{{
    {" - ", "| |", "   ", "| |", " - "}, // 0
    {"   ", "  |", "   ", "  |", "   "}, // 1
    {" - ", "  |", " - ", "|  ", " - "}, // 2
    {" - ", "  |", " - ", "  |", " - "}, // 3
    {"   ", "| |", " - ", "  |", "   "}, // 4
    {" - ", "|  ", " - ", "  |", " - "}, // 5
    {" - ", "|  ", " - ", "| |", " - "}, // 6
    {" - ", "  |", "   ", "  |", "   "}, // 7
    {" - ", "| |", " - ", "| |", " - "}, // 8
    {" - ", "| |", " - ", "  |", " - "}, // 9
}};
static const std::array<std::string, 5> MINUS_EXPECT{
    "   ", "   ", " - ", "   ", "   "};

static std::string buildExpected(const std::string &s)
{
  std::array<std::string, 5> rows{};
  for (std::size_t idx = 0; idx < s.size(); ++idx)
  {
    char c = s[idx];
    const std::array<std::string, 5> *g = nullptr;
    if (c == '-')
      g = &MINUS_EXPECT;
    else
      g = &DIGITS_EXPECT[static_cast<std::size_t>(c - '0')];
    for (int r = 0; r < 5; ++r)
    {
      rows[r] += (*g)[static_cast<std::size_t>(r)];
      if (idx + 1 < s.size())
        rows[r] += ' ';
    }
  }
  std::string result;
  for (int r = 0; r < 5; ++r)
  {
    result += rows[static_cast<std::size_t>(r)];
    result += '\n';
  }
  return result;
}

// ---- Mehr Tests ----

TEST_CASE("printLargeDigit_all_digits")
{
  for (int d = 0; d <= 9; ++d)
  {
    std::ostringstream os;
    printLargeDigit(d, os);
    // Erwartung direkt aus DIGITS_EXPECT
    std::string exp;
    for (int r = 0; r < 5; ++r)
    {
      exp += DIGITS_EXPECT[static_cast<std::size_t>(d)][static_cast<std::size_t>(r)];
      exp += '\n';
    }
    REQUIRE(os.str() == exp);
  }
}

TEST_CASE("printLargeDigit_invalid_throws")
{
  std::ostringstream os;
  REQUIRE_THROWS_AS(printLargeDigit(-1, os), std::invalid_argument);
  REQUIRE_THROWS_AS(printLargeDigit(10, os), std::invalid_argument);
}

TEST_CASE("printLargeNumber_positive")
{
  std::ostringstream os;
  printLargeNumber(12039, os);
  REQUIRE(os.str() == buildExpected("12039"));
}

TEST_CASE("printLargeNumber_negative")
{
  std::ostringstream os;
  printLargeNumber(-12, os);
  REQUIRE(os.str() == buildExpected("-12"));
}

TEST_CASE("printLargeNumber_zero")
{
  std::ostringstream os;
  printLargeNumber(0, os);
  REQUIRE(os.str() == buildExpected("0"));
}

TEST_CASE("printLargeNumber_single_digits_match")
{
  for (int d = 0; d <= 9; ++d)
  {
    std::ostringstream os;
    printLargeNumber(d, os);
    REQUIRE(os.str() == buildExpected(std::to_string(d)));
  }
}

TEST_CASE("printLargeNumber_full_sequence_1234567890")
{
  std::ostringstream os;
  printLargeNumber(1234567890, os);
  REQUIRE(os.str() == buildExpected("1234567890"));
}

TEST_CASE("printLargeNumber_negative_single_digit")
{
  std::ostringstream os;
  printLargeNumber(-5, os);
  REQUIRE(os.str() == buildExpected("-5"));
}

TEST_CASE("printLargeNumber_INT_MIN")
{
  std::ostringstream os;
  const int v = std::numeric_limits<int>::min();
  printLargeNumber(v, os);
  REQUIRE(os.str() == buildExpected(std::to_string(v)));
}

TEST_CASE("printLargeNumber_has_five_lines")
{
  auto assert_five_lines = [](const std::string &s)
  {
    // Count '\n'
    REQUIRE(std::count(s.begin(), s.end(), '\n') == 5);
    // Ends with a newline
    REQUIRE(!s.empty());
    REQUIRE(s.back() == '\n');
  };

  {
    std::ostringstream os;
    printLargeNumber(0, os);
    assert_five_lines(os.str());
  }
  {
    std::ostringstream os;
    printLargeNumber(42, os);
    assert_five_lines(os.str());
  }
  {
    std::ostringstream os;
    printLargeNumber(-7, os);
    assert_five_lines(os.str());
  }
}

TEST_CASE("printLargeDigit_has_five_lines_and_trailing_newline")
{
  for (int d = 0; d <= 9; ++d)
  {
    std::ostringstream os;
    printLargeDigit(d, os);
    const std::string out = os.str();
    REQUIRE(std::count(out.begin(), out.end(), '\n') == 5);
    REQUIRE(!out.empty());
    REQUIRE(out.back() == '\n');
  }
}

TEST_CASE("printLargeNumber_exact_one_space_between_digits")
{
  const std::string num = "907";
  std::ostringstream os;
  printLargeNumber(907, os);
  const std::string out = os.str();

  REQUIRE(out == buildExpected(num));
}