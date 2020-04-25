project(daily)

# add_definitions(-fprofile-arcs -ftest-coverage)

file(GLOB DAILY_FILES
   "src/*.h"
   "src/*.cpp"
)

file(GLOB DAILY_TEST_FILES
   "test/*.h"
   "test/*.cpp"
)

# message("This is a cmake project binary dir" ${PROJECT_BINARY_DIR})
# message("This is a cmake binary dir" ${CMAKE_BINARY_DIR})
# message("This is a cmake source dir" ${CMAKE_SOURCE_DIR})
# message("This is a cmake object dir" ${OBJECT_DIR})

include_directories(src)
add_executable(${PROJECT_NAME} ${DAILY_FILES} ${DAILY_TEST_FILES})
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
