#define CATCH_CONFIG_MAIN
#include "lib.hpp"
#include <catch2/catch.hpp>

using Ion_DrumPad::App;

TEST_CASE("Public variables", "lib")
{
    App app;

    REQUIRE(app.window_size.width == 800);
    REQUIRE(app.window_size.height == 600);
    REQUIRE(app.window_title == "Ion Drum Pad");
    REQUIRE(app.config_path == "config.json");
    #ifdef _WIN32
    REQUIRE(app.default_font == "C:\\Windows\\Fonts\\arial.ttf");
    #elif __linux__
    REQUIRE(app.default_font == "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");
    #endif
    REQUIRE(app.ms_delay.count() == 16);
}

TEST_CASE("Callbacks don't throw", "lib")
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