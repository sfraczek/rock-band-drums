#include "config_file.hpp"
#include "temporary_file.hpp"
#include <catch2/catch.hpp>

TEST_CASE("Read Config from file", "config_file")
{
    TemporaryFile tmp_config_file;
    tmp_config_file.Write(Ion_DrumPad::ConfigFile::default_config);
    Ion_DrumPad::ConfigFile::Config config(tmp_config_file.Name());

    REQUIRE(config.window_size.width == 1024);
    REQUIRE(config.window_size.height == 768);
    REQUIRE(config.title.text == "Ion Audio IED08 Drum Rocker for PlayStation binding");
    REQUIRE(config.title.rgb == std::vector<uint8_t>{0, 111, 205});

    auto &drums = config.drums;

    REQUIRE(drums.size() == 8);

    REQUIRE(drums[0].name == "HiHat");
    REQUIRE(drums[0].sound_file == "sounds/Analog Hihat 1.ogg");
    REQUIRE(drums[0].image_file == "images/hihat/drum-kit-hi-hat.jpg");
    REQUIRE(drums[0].keyboard_buttons_combination == std::vector<uint32_t>{7});
    REQUIRE(drums[0].joystick_buttons_combination == std::vector<uint32_t>{3, 11, 107});
    REQUIRE(drums[0].position_on_screen.x == 200);
    REQUIRE(drums[0].position_on_screen.y == 150);
    REQUIRE(drums[0].radius == 80);
    REQUIRE(drums[0].rgb == std::vector<uint8_t>{255, 255, 0});

    REQUIRE(drums[1].name == "Snare");
    REQUIRE(drums[1].sound_file == "sounds/Analog Snare 1.ogg");
    REQUIRE(drums[1].image_file == "images/snare/rogers 1964 silver sparkle powertone (cleveland)_thumb.jpg");
    REQUIRE(drums[1].keyboard_buttons_combination == std::vector<uint32_t>{18});
    REQUIRE(drums[1].joystick_buttons_combination == std::vector<uint32_t>{2, 10});
    REQUIRE(drums[1].position_on_screen.x == 100);
    REQUIRE(drums[1].position_on_screen.y == 350);
    REQUIRE(drums[1].radius == 80);
    REQUIRE(drums[1].rgb == std::vector<uint8_t>{255, 0, 0});

    REQUIRE(drums[2].name == "Tom-tom1");
    REQUIRE(drums[2].sound_file == "sounds/General Room Hi Tom.ogg");
    REQUIRE(drums[2].image_file == "images/tom/drum-kit-1488406125CbG.jpg");
    REQUIRE(drums[2].keyboard_buttons_combination == std::vector<uint32_t>{999});
    REQUIRE(drums[2].joystick_buttons_combination == std::vector<uint32_t>{3, 10});
    REQUIRE(drums[2].position_on_screen.x == 300);
    REQUIRE(drums[2].position_on_screen.y == 300);
    REQUIRE(drums[2].radius == 80);
    REQUIRE(drums[2].rgb == std::vector<uint8_t>{255, 255, 0});

    REQUIRE(drums[3].name == "Tom-tom2");
    REQUIRE(drums[3].sound_file == "sounds/General Room Mid Tom.ogg");
    REQUIRE(drums[3].image_file == "images/tom/drum-kit-1488406125CbG.jpg");
    REQUIRE(drums[3].keyboard_buttons_combination == std::vector<uint32_t>{999});
    REQUIRE(drums[3].joystick_buttons_combination == std::vector<uint32_t>{0, 10});
    REQUIRE(drums[3].position_on_screen.x == 500);
    REQUIRE(drums[3].position_on_screen.y == 300);
    REQUIRE(drums[3].radius == 80);
    REQUIRE(drums[3].rgb == std::vector<uint8_t>{0, 0, 255});

    REQUIRE(drums[4].name == "Tom-tom3");
    REQUIRE(drums[4].sound_file == "sounds/General Room Low Tom.ogg");
    REQUIRE(drums[4].image_file == "images/tom/drum-kit-1488406125CbG.jpg");
    REQUIRE(drums[4].keyboard_buttons_combination == std::vector<uint32_t>{999});
    REQUIRE(drums[4].joystick_buttons_combination == std::vector<uint32_t>{1, 10});
    REQUIRE(drums[4].position_on_screen.x == 700);
    REQUIRE(drums[4].position_on_screen.y == 350);
    REQUIRE(drums[4].radius == 80);
    REQUIRE(drums[4].rgb == std::vector<uint8_t>{0, 255, 0});

    REQUIRE(drums[5].name == "Crash");
    REQUIRE(drums[5].sound_file == "sounds/General Crash.ogg");
    REQUIRE(drums[5].image_file == "images/cymbal/320px-Bellotti_Cymbal.jfif");
    REQUIRE(drums[5].keyboard_buttons_combination == std::vector<uint32_t>{999});
    REQUIRE(drums[5].joystick_buttons_combination == std::vector<uint32_t>{1, 11, 107});
    REQUIRE(drums[5].position_on_screen.x == 600);
    REQUIRE(drums[5].position_on_screen.y == 150);
    REQUIRE(drums[5].radius == 80);
    REQUIRE(drums[5].rgb == std::vector<uint8_t>{0, 255, 0});

    REQUIRE(drums[6].name == "Ride");
    REQUIRE(drums[6].sound_file == "sounds/General Ride.ogg");
    REQUIRE(drums[6].image_file == "images/cymbal/320px-Bellotti_Cymbal.jfif");
    REQUIRE(drums[6].keyboard_buttons_combination == std::vector<uint32_t>{999});
    REQUIRE(drums[6].joystick_buttons_combination == std::vector<uint32_t>{0, 11, 107});
    REQUIRE(drums[6].position_on_screen.x == 400);
    REQUIRE(drums[6].position_on_screen.y == 100);
    REQUIRE(drums[6].radius == 80);
    REQUIRE(drums[6].rgb == std::vector<uint8_t>{0, 0, 255});

    REQUIRE(drums[7].name == "Kick");
    REQUIRE(drums[7].sound_file == "sounds/Analog Kick 1.ogg");
    REQUIRE(drums[7].image_file == "images/kick/drum-kit-pedal.jpg");
    REQUIRE(drums[7].keyboard_buttons_combination == std::vector<uint32_t>{7, 18});
    REQUIRE(drums[7].joystick_buttons_combination == std::vector<uint32_t>{4});
    REQUIRE(drums[7].position_on_screen.x == 400);
    REQUIRE(drums[7].position_on_screen.y == 500);
    REQUIRE(drums[7].radius == 80);
    REQUIRE(drums[7].rgb == std::vector<uint8_t>{255, 128, 0});
}