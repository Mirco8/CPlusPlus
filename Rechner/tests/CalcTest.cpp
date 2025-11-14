#include "Calc.hpp"

#include <catch2/catch_test_macros.hpp>

#include <cstdlib>

// TODO: Add more tests

TEST_CASE("testOnePlusOne")
{
  auto result = calc(1, 1, '+');
  REQUIRE(result == 2);
}
