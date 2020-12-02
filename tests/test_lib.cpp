#define CATCH_CONFIG_MAIN
#include "lib.hpp"
#include "config_file.hpp"
#include "temporary_file.hpp"
#include <catch2/catch.hpp>

TEST_CASE("Public variables", "lib")
{
    TemporaryFile tmp_config_file;
    tmp_config_file.Write(Ion_DrumPad::ConfigFile::default_config);
    Ion_DrumPad::App app(tmp_config_file.Name());

    REQUIRE(app.window_title == "Ion Drum Pad");
    REQUIRE(app.config_path == tmp_config_file.Name());
#ifdef _WIN32
    REQUIRE(app.default_font == "C:\\Windows\\Fonts\\arial.ttf");
#elif __linux__
    REQUIRE(app.default_font == "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");
#endif
    REQUIRE(app.ms_delay.count() == 16);
    REQUIRE(app.button_axis_offset == 100);
}

TEST_CASE("Callbacks don't throw", "lib")
{
    TemporaryFile tmp_config_file;
    tmp_config_file.Write(Ion_DrumPad::ConfigFile::default_config);
    Ion_DrumPad::App app(tmp_config_file.Name());

    auto key_code = 12u;
    auto joystick_id = 1u;
    auto joystick_button = 5u;
    auto axis = 7u;
    auto force = 100u;
    REQUIRE_NOTHROW(app.KeyPressedCallback(12));
    REQUIRE_NOTHROW(app.KeyReleasedCallback(12));
    REQUIRE_NOTHROW(app.JoystickButtonPressedCallback(joystick_id, joystick_button));
    REQUIRE_NOTHROW(app.JoystickButtonReleasedCallback(joystick_id, joystick_button));
    REQUIRE_NOTHROW(app.JoystickDisconnectedCallback(joystick_id));
    REQUIRE_NOTHROW(app.JoystickConnectedCallback(joystick_id));
    REQUIRE_NOTHROW(app.JoystickMovedCallback(axis, force));
    // Cannot have twice the same button presset at the same time
    REQUIRE(app.joystick_buttons_pressed == std::vector<uint32_t>{joystick_button, axis + app.button_axis_offset});
}