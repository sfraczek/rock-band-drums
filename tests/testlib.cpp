#define CATCH_CONFIG_MAIN
#include "lib.hpp"
#include "util.hpp"
#include <catch2/catch.hpp>

using Ion_DrumPad::App;

TEST_CASE("Public variables", "App")
{
    App app;

    REQUIRE(app.window_size.width == 800);
    REQUIRE(app.window_size.height == 600);
    REQUIRE(app.window_title == "Ion Drum Pad");
}

TEST_CASE("Callbacks don't throw", "App")
{
    App app;

    auto key_code = 12u;
    auto joystick_id = 1u;
    auto joystick_button = 5u;
    REQUIRE_NOTHROW(app.KeyPressedCallback(12));
    REQUIRE_NOTHROW(app.KeyReleasedCallback(12));
    REQUIRE_NOTHROW(app.JoystickButtonPressedCallback(joystick_id, joystick_button));
    REQUIRE_NOTHROW(app.JoystickButtonReleasedCallback(joystick_id, joystick_button));
    REQUIRE_NOTHROW(app.JoystickDisconnectedCallback(joystick_id));
    REQUIRE_NOTHROW(app.JoystickConnectedCallback(joystick_id));
}

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

    REQUIRE(RemoveSubset({14}, {10, 11, 12, 13}) == std::vector<uint32_t>{});
    REQUIRE(RemoveSubset({14, 15}, {10, 11, 12, 13}) == std::vector<uint32_t>{});
    REQUIRE(RemoveSubset({10, 15}, {10, 11, 12, 13}) == std::vector<uint32_t>{});
    REQUIRE(RemoveSubset({10, 11, 12, 13, 14}, {10, 11, 12, 13}) == std::vector<uint32_t>{});
    REQUIRE(RemoveSubset({10, 11}, {}) == std::vector<uint32_t>{});
    REQUIRE(RemoveSubset({}, {}) == std::vector<uint32_t>{});
}

TEST_CASE("SortMakeUnique", "util")
{
    auto ReturnSortMakeUnique = [](std::vector<uint32_t>&& sequence) {Ion_DrumPad::SortMakeUnique(sequence); return sequence; };
    REQUIRE(ReturnSortMakeUnique({1}) == std::vector<uint32_t>{1});
    REQUIRE(ReturnSortMakeUnique({}) == std::vector<uint32_t>{});
    REQUIRE(ReturnSortMakeUnique({0, 4, 2, 3, 4, 0, 5}) == std::vector<uint32_t>{0, 2, 3, 4, 5});
}
