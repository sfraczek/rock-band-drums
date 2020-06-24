#include "config_file.hpp"
#include <catch2/catch.hpp>
#include <fstream>
#include <filesystem>

using namespace Ion_DrumPad::ConfigFile;
using Ion_DrumPad::Drum;

struct TemporaryFile
{
    TemporaryFile()
    {
        auto directory = std::filesystem::temp_directory_path();
        std::filesystem::path filename = std::tmpnam(nullptr);
        auto file_path = directory / filename;
        fname = file_path.string();
    }

    ~TemporaryFile()
    {
        if (fs.is_open())
            fs.close();
        if (!fname.empty())
            std::filesystem::remove(fname);
    }

    void Write(const char *data)
    {
        fs.open(fname);
        fs << data;
        fs.close();
    }

    std::string Name()
    {
        return fname;
    }

private:
    std::string fname;
    std::ofstream fs;
};

TEST_CASE("Read Config from file", "config_file")
{
    TemporaryFile tmp_config_file;
    tmp_config_file.Write(default_config);
    Config config(tmp_config_file.Name());
    auto& drums = config.drums;

    REQUIRE(drums.size() == 3);

    REQUIRE(drums[0].name == "HiHat");
    REQUIRE(drums[0].sound_file == "sounds/Analog Hihat 1.ogg");
    REQUIRE(drums[0].image_file == "images/hihat/drum-kit-hi-hat.jpg");
    REQUIRE(drums[0].keyboard_buttons_combination == std::vector<uint32_t>{7});
    REQUIRE(drums[0].joystick_buttons_combination == std::vector<uint32_t>{0});
    REQUIRE(drums[0].position_on_screen.x == 100);
    REQUIRE(drums[0].position_on_screen.y == 100);
    REQUIRE(drums[0].radius == 80);

    REQUIRE(drums[1].name == "Snare");
    REQUIRE(drums[1].sound_file == "sounds/Analog Snare 1.ogg");
    REQUIRE(drums[1].image_file == "images/snare/rogers 1964 silver sparkle powertone (cleveland)_thumb.jpg");
    REQUIRE(drums[1].keyboard_buttons_combination == std::vector<uint32_t>{18});
    REQUIRE(drums[1].joystick_buttons_combination == std::vector<uint32_t>{1});
    REQUIRE(drums[1].position_on_screen.x == 300);
    REQUIRE(drums[1].position_on_screen.y == 100);
    REQUIRE(drums[1].radius == 80);

    REQUIRE(drums[2].name == "Kick");
    REQUIRE(drums[2].sound_file == "sounds/Analog Kick 1.ogg");
    REQUIRE(drums[2].image_file == "images/kick/drum-kit-pedal.jpg");
    REQUIRE(drums[2].keyboard_buttons_combination == std::vector<uint32_t>{7, 18});
    REQUIRE(drums[2].joystick_buttons_combination == std::vector<uint32_t>{2});
    REQUIRE(drums[2].position_on_screen.x == 600);
    REQUIRE(drums[2].position_on_screen.y == 100);
    REQUIRE(drums[2].radius == 80);
}