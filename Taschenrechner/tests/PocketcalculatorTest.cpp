#include "Pocketcalculator.hpp"

#include <catch2/catch_test_macros.hpp>
#include <sstream>

//TODO: Add more tests

TEST_CASE("testEmptyStream") {
  std::istringstream input{};
  std::ostringstream output{};
  pocketcalculator(input, output);
  REQUIRE(output.str() == "");
}
