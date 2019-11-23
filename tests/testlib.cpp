#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "lib.hpp"


TEST_CASE("integers are added", "[add]")
{
    Program program;

    REQUIRE(program.add(1, 0) == 1);
    REQUIRE(program.add(1, 1) == 2);
    REQUIRE(program.add(-5, 11) == 6);
    REQUIRE(program.add(-1, -1) == -2);
}

TEST_CASE( "This test should fail", "[add]" ) 
{
    Program program;

    SECTION( "So far so good" ) {
        REQUIRE(program.add(122, 1) == 123);
    }

    SECTION( "it fails in this section" ) {
        REQUIRE(program.add(99, 5) == 1);
    }
}
