project(daily)

file(GLOB DAILY_FILES
   "src/*.h"
   "src/*.cpp"
)

file(GLOB DAILY_TEST_FILES
   "test/*.h"
   "test/*.cpp"
)

include_directories(src)
add_executable(${PROJECT_NAME} ${DAILY_FILES} ${DAILY_TEST_FILES})
target_link_libraries(${PROJECT_NAME} gtest_main)


