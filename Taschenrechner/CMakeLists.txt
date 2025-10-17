#[===[ LIBRARY ]===]

add_library("${CPL_TARGET_WEEK_PREFIX}ex01_pocketcalculator"
    "lib/Pocketcalculator.cpp"
)

target_include_directories("${CPL_TARGET_WEEK_PREFIX}ex01_pocketcalculator" PUBLIC "lib")

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}ex01_pocketcalculator" PUBLIC
    "w02_ex02_calc_lib"
    "w03_ex01_seven_segment"
)


#[===[ APPLICATION ]===]

add_executable("${CPL_TARGET_WEEK_PREFIX}ex01_pocketcalculator_app"
"app/PocketcalculatorApp.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}ex01_pocketcalculator_app" PRIVATE
"${CPL_TARGET_WEEK_PREFIX}ex01_pocketcalculator"
)


#[===[ TESTS ]===]


add_executable("${CPL_TARGET_WEEK_PREFIX}ex01_pocketcalculator_tests"
    "tests/PocketcalculatorTests.cpp"
)

target_link_libraries("${CPL_TARGET_WEEK_PREFIX}ex01_pocketcalculator_tests" PRIVATE
    "${CPL_TARGET_WEEK_PREFIX}ex01_pocketcalculator"
    "Catch2::Catch2WithMain"
)

catch_discover_tests("${CPL_TARGET_WEEK_PREFIX}ex01_pocketcalculator_tests")
