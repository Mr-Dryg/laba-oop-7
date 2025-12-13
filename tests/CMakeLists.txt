include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.0
  TLS_VERIFY false
)
FetchContent_MakeAvailable(googletest)

set(TEST_SOURCES
  test_main.cpp
  test01.cpp
)

add_executable(tests ${TEST_SOURCES})
target_link_libraries(tests gtest_main gmock lib)

include(GoogleTest)
gtest_discover_tests(tests)