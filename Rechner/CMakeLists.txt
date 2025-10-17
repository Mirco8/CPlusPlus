#[===[ LIBRARY ]===]

add_library("${CPL_TARGET_WEEK_PREFIX}ex02_calc_lib"
  "lib/Calc.cpp"
)

target_include_directories("${CPL_TARGET_WEEK_PREFIX}ex02_calc_lib" PUBLIC "lib")


#[===[ APPLICATION ]===]

add_executable("${CPL_TARGET_WEEK_PREFIX}ex02_calc_app"
  "app/CalcApp.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}ex02_calc_app" PRIVATE
  "${CPL_TARGET_WEEK_PREFIX}ex02_calc_lib"
)


#[===[ TESTS ]===]


add_executable("${CPL_TARGET_WEEK_PREFIX}ex02_calc_tests"
  "tests/CalcTests.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}ex02_calc_tests" PRIVATE
  "${CPL_TARGET_WEEK_PREFIX}ex02_calc_lib"
  "Catch2::Catch2WithMain"
)

catch_discover_tests("${CPL_TARGET_WEEK_PREFIX}ex02_calc_tests")
