#define CATCH_CONFIG_MAIN
#include "lib.hpp"
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

TEST_CASE("GetAllSubsets", "App")
{
    App app;

    REQUIRE(app.GetAllSubsets({}) == std::vector<std::vector<uint32_t>>{});
    REQUIRE(app.GetAllSubsets({0, 1, 2, 3}) == std::vector<std::vector<std::vector<uint32_t>>>{
                                                   {{0}, {1, 2, 3}}, {{1}, {0, 2, 3}}, {{0, 1}, {2, 3}}, {{2}, {0, 1, 3}}, {{0, 2}, {1, 3}}, {{1, 2}, {0, 3}}, {{0, 1, 2}, {3}}, {0, 1, 2, 3}});
}
TEST_CASE("GetAllSubsetsSorted", "App")
{
    App app;

    REQUIRE(app.GetAllSubsetsSorted({}) == std::vector<std::vector<uint32_t>>{});
    REQUIRE(app.GetAllSubsetsSorted({0, 1, 2, 3}) == std::vector<std::vector<std::vector<<uint32_t>>>{
                                                         {0, 1, 2, 3}, {{0, 1, 2}, {3}}, {{0, 1, 3}, {2}}, {{0, 2, 3}, {1}}, {{1, 2, 3}, {0}}, {{0, 1}, {2, 3}}, {{0, 2}, {1, 3}}, {{1, 2}, {0, 3}}});
}