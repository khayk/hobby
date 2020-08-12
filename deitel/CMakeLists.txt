project(deitel)

# add_definitions(-fprofile-arcs -ftest-coverage)

file(GLOB DEITEL_FILES
   "src/*.h"
   "src/*.cpp"
)

file(GLOB DEITEL_TEST_FILES
   "test/*.h"
   "test/*.cpp"
)

include_directories(src)
add_executable(${PROJECT_NAME} ${DEITEL_FILES} ${DEITEL_TEST_FILES})
target_link_libraries(${PROJECT_NAME} gtest_main)
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
