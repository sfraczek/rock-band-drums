#include "util.hpp"
#include <catch2/catch.hpp>

TEST_CASE("RemoveSubset", "util")
{
    using Ion_DrumPad::RemoveSubset;
    REQUIRE(RemoveSubset({10}, {10, 11, 12, 13}) == std::vector<uint32_t>{11, 12, 13});
    REQUIRE(RemoveSubset({11}, {10, 11, 12, 13}) == std::vector<uint32_t>{10, 12, 13});
    REQUIRE(RemoveSubset({13}, {10, 11, 12, 13}) == std::vector<uint32_t>{10, 11, 12});
    REQUIRE(RemoveSubset({}, {10, 11, 12, 13}) == std::vector<uint32_t>{10, 11, 12, 13});
    REQUIRE(RemoveSubset({10, 11}, {10, 11, 12, 13}) == std::vector<uint32_t>{12, 13});
    REQUIRE(RemoveSubset({12, 13}, {10, 11, 12, 13}) == std::vector<uint32_t>{10, 11});
    REQUIRE(RemoveSubset({10, 13}, {10, 11, 12, 13}) == std::vector<uint32_t>{11, 12});
    REQUIRE(RemoveSubset({10, 11, 12, 13}, {10, 11, 12, 13}) == std::vector<uint32_t>{});

    REQUIRE(RemoveSubset({14}, {10, 11, 12, 13}).has_value() == false);
    REQUIRE(RemoveSubset({14, 15}, {10, 11, 12, 13}).has_value() == false);
    REQUIRE(RemoveSubset({10, 15}, {10, 11, 12, 13}).has_value() == false);
    REQUIRE(RemoveSubset({10, 11, 12, 13, 14}, {10, 11, 12, 13}).has_value() == false);
    REQUIRE(RemoveSubset({10, 11}, {}).has_value() == false);
    REQUIRE(RemoveSubset({}, {}) == std::vector<uint32_t>{});
}

TEST_CASE("SortMakeUnique", "util")
{
    auto ReturnSortMakeUnique = [](std::vector<uint32_t>&& sequence) {Ion_DrumPad::SortMakeUnique(sequence); return sequence; };
    REQUIRE(ReturnSortMakeUnique({1}) == std::vector<uint32_t>{1});
    REQUIRE(ReturnSortMakeUnique({}) == std::vector<uint32_t>{});
    REQUIRE(ReturnSortMakeUnique({0, 4, 2, 3, 4, 0, 5}) == std::vector<uint32_t>{0, 2, 3, 4, 5});
}
