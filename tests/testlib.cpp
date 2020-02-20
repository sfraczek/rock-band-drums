#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "lib.hpp"

using Ion_DrumPad::App;

TEST_CASE("App", "Public variables")
{
    App app;

    REQUIRE(app.window_size.width == 800);
    REQUIRE(app.window_size.height == 600);
    REQUIRE(app.window_title == "Ion Drum Pad");
}

TEST_CASE("App", "Callbacks don't throw")
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
