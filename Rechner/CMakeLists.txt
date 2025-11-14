Include(FetchContent)
 
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.7.0
  URL_HASH       "SHA256=75b04c94471a70680f10f5d0d985bd1a96b8941d040d6a7bfd43f6c6b1de9daf"
)
 
FetchContent_MakeAvailable(Catch2)
cmake_minimum_required(VERSION 3.19)
 
project("calculator"
    LANGUAGES CXX
)
 
set(CMAKE_CXX_STANDARD 20)
 
add_library("CalcLib" "lib/Calc.cpp")
target_include_directories("CalcLib" PUBLIC "lib")
 
add_executable("CalcTest" "tests/CalcTest.cpp")
target_link_libraries("CalcTest" PRIVATE "CalcLib" "Catch2::Catch2WithMain")
 
add_executable("CalcApp" "app/CalcApp.cpp")
target_link_libraries("CalcApp" PRIVATE "CalcLib")