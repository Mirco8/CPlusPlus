#include "Sevensegment.hpp"

#include <catch2/catch_test_macros.hpp>

#include <sstream>

//TODO: Add more tests

TEST_CASE("testLargeDigitZero") {
  std::ostringstream output{};
  printLargeDigit(0, output);
  REQUIRE(output.str() == " - \n"
                          "| |\n"
                          "   \n"
                          "| |\n"
                          " - \n");
}

static const std::array<std::array<std::string, 5>, 10> DIGITS_EXPECT {{
  { " - ", "| |", "   ", "| |", " - " }, // 0
  { "   ", "  |", "   ", "  |", "   " }, // 1
  { " - ", "  |", " - ", "|  ", " - " }, // 2
  { " - ", "  |", " - ", "  |", " - " }, // 3
  { "   ", "| |", " - ", "  |", "   " }, // 4
  { " - ", "|  ", " - ", "  |", " - " }, // 5
  { " - ", "|  ", " - ", "| |", " - " }, // 6
  { " - ", "  |", "   ", "  |", "   " }, // 7
  { " - ", "| |", " - ", "| |", " - " }, // 8
  { " - ", "| |", " - ", "  |", " - " }, // 9
}};
static const std::array<std::string, 5> MINUS_EXPECT {
  "   ", "   ", " - ", "   ", "   "
};

static std::string buildExpected(const std::string& s) {
  std::array<std::string, 5> rows{};
  for (std::size_t idx = 0; idx < s.size(); ++idx) {
    char c = s[idx];
    const std::array<std::string, 5>* g = nullptr;
    if (c == '-') g = &MINUS_EXPECT;
    else g = &DIGITS_EXPECT[static_cast<std::size_t>(c - '0')];
    for (int r = 0; r < 5; ++r) {
      rows[r] += (*g)[static_cast<std::size_t>(r)];
      if (idx + 1 < s.size()) rows[r] += ' ';
    }
  }
  std::string result;
  for (int r = 0; r < 5; ++r) {
    result += rows[static_cast<std::size_t>(r)];
    result += '\n';
  }
  return result;
}

// ---- Mehr Tests ----

TEST_CASE("printLargeDigit_all_digits") {
  for (int d = 0; d <= 9; ++d) {
    std::ostringstream os;
    printLargeDigit(d, os);
    // Erwartung direkt aus DIGITS_EXPECT
    std::string exp;
    for (int r = 0; r < 5; ++r) {
      exp += DIGITS_EXPECT[static_cast<std::size_t>(d)][static_cast<std::size_t>(r)];
      exp += '\n';
    }
    REQUIRE(os.str() == exp);
  }
}

TEST_CASE("printLargeDigit_invalid_throws") {
  std::ostringstream os;
  REQUIRE_THROWS_AS(printLargeDigit(-1, os), std::invalid_argument);
  REQUIRE_THROWS_AS(printLargeDigit(10, os), std::invalid_argument);
}

TEST_CASE("printLargeNumber_positive") {
  std::ostringstream os;
  printLargeNumber(12039, os);
  REQUIRE(os.str() == buildExpected("12039"));
}

TEST_CASE("printLargeNumber_negative") {
  std::ostringstream os;
  printLargeNumber(-12, os);
  REQUIRE(os.str() == buildExpected("-12"));
}

TEST_CASE("printLargeNumber_zero") {
  std::ostringstream os;
  printLargeNumber(0, os);
  REQUIRE(os.str() == buildExpected("0"));
}
