project(patterns)

file(GLOB INTRO_FILES
   "src/*.h"
   "src/*.cpp"
)

file(GLOB INTRO_TEST_FILES
   "test/*.h"
   "test/*.cpp"
)

include_directories(src)
add_executable(${PROJECT_NAME} ${INTRO_FILES} ${INTRO_TEST_FILES})
target_link_libraries(${PROJECT_NAME} gtest gtest_main)