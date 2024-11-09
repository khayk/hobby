cmake_minimum_required(VERSION 3.5)

message("CMAKE_TOOLCHAIN_FILE: ${CMAKE_TOOLCHAIN_FILE}")
message("VCPKG_ROOT          : $ENV{VCPKG_ROOT}")

set(CMAKE_VERBOSE_MAKEFILE ON)

if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
   set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
      CACHE STRING "")
   message("CMAKE_TOOLCHAIN_FILE: ${CMAKE_TOOLCHAIN_FILE}")
endif()

project(deitel)

# add_definitions(-fprofile-arcs -ftest-coverage)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB DEITEL_FILES
   "src/*.h"
   "src/*.cpp"
)

file(GLOB DEITEL_TEST_FILES
   "test/*.h"
   "test/*.cpp"
)

enable_testing()
find_package(GTest REQUIRED)
message("Gtest libraries       : ${GTEST_BOTH_LIBRARIES}")

include_directories(src)
add_executable(${PROJECT_NAME} ${DEITEL_FILES} ${DEITEL_TEST_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE
   ${GTEST_BOTH_LIBRARIES}
)
# target_link_libraries(${PROJECT_NAME} -fprofile-arcs)

if(CMAKE_COMPILER_IS_GNUCXX AND COVERAGE)
   set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
   include(CodeCoverage)

   append_coverage_compiler_flags()

   setup_target_for_coverage_lcov(
      NAME        ${PROJECT_NAME}_coverage
      EXECUTABLE  ${PROJECT_NAME} coverage
      EXCLUDE     ${CMAKE_BINARY_DIR}/googletest-src/*)

   target_link_libraries(${PROJECT_NAME} gcov)
endif()

# Later review this
#  https://github.com/jhbell/cmake-gcov/blob/master/CMakeLists.txt

# Several helpful commands
# gcov -b ./daily/CMakeFiles/daily.dir/src/DailyCodingProblem.cpp.o | grep -A 5 "daily" > CoverageSummary.tmp
# find ./ -name "*.cpp.o" -exec gcov -b {} \; | grep -A 5 "daily" > CoverageSummary.tmp
# sudo apt install lcov
# lcov --capture --directory . --output-file main_coverage.info
# genhtml main_coverage.info --output-directory out
