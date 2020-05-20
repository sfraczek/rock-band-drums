# Testing library

# Adds Catch2::Catch2
FetchContent_Declare(
    catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v2.11.0
    GIT_PROGRESS   TRUE
    GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(catch2)
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/contrib)
include(Catch)

# Tests need to be added as executables first
add_executable(testsuite test_lib.cpp test_util.cpp)

# Should be linked to the main library, as well as the Catch2 testing library
target_link_libraries(testsuite PRIVATE libraries Catch2::Catch2)

# Somewhat speed up Catch2 compile times
target_compile_definitions(testsuite
    PRIVATE
        CATCH_CONFIG_FAST_COMPILE
        CATCH_CONFIG_DISABLE_MATCHERS
)

include(CTest)
catch_discover_tests(testsuite)