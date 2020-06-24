#include "config_file.hpp"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <filesystem>

#include <nlohmann/json.hpp>

#include "algebra.hpp"
#include "drum.hpp"
#include "util.hpp"

using json = nlohmann::json;

namespace Ion_DrumPad
{
    void from_json(const json &j, Position &p)
    {
        j.at("x").get_to(p.x);
        j.at("y").get_to(p.y);
    }

    void from_json(const json &j, Drum &d)
    {
        j.at("name").get_to(d.name);
        j.at("sound_file").get_to(d.sound_file);
        j.at("image_file").get_to(d.image_file);
        j.at("keyboard_buttons_combination").get_to(d.keyboard_buttons_combination);
        SortMakeUnique(d.keyboard_buttons_combination);
        j.at("joystick_buttons_combination").get_to(d.joystick_buttons_combination);
        SortMakeUnique(d.joystick_buttons_combination);
        j.at("position_on_screen").get_to(d.position_on_screen);
        j.at("radius").get_to(d.radius);
    }

    namespace ConfigFile
    {
        void from_json(const json &j, ConfigFile::Config &c)
        {
            for (auto &js_drum : j["drums"])
            {
                std::cout << js_drum << "\n";
                c.drums.emplace_back(js_drum.get<Drum>());
            }
        }

        Config::Config(const std::string &file)
        {
            std::ifstream ifs(file);
            if (!ifs.is_open())
            {
                std::filesystem::path fpath(file);
                std::string to_append = fpath.string() + " in path: " + std::filesystem::current_path().string();
                if (std::filesystem::exists(file))
                {
                    throw std::runtime_error("File does not exist: " + to_append);
                }
                else
                {
                    throw std::runtime_error("Could not open file: " + to_append);
                }
            }

            json js_config = json::parse(ifs);

            js_config.get_to(*this);

            Validate();
        }

        void Config::Validate()
        {
            for (size_t i = 0; i < drums.size(); i++)
            {
                for (size_t j = 0; j < drums.size(); j++)
                {
                    if (i != j && drums[i].name == drums[j].name)
                        throw std::invalid_argument("Repeated drum name '" + drums[i].name +
                                                    "' encountered in the config. Drum names must be unique.");
                }
            }
        }

        const char *default_config = R"(
{
    "drums":
    [
        {
            "name": "HiHat",
            "sound_file": "sounds/Analog Hihat 1.ogg",
            "image_file": "images/hihat/drum-kit-hi-hat.jpg",
            "keyboard_buttons_combination": [
                7
            ],
            "joystick_buttons_combination": [
                0
            ],
            "position_on_screen": {
                "x": 100,
                "y": 100
            },
            "radius": 80
        },
        {
            "name": "Snare",
            "sound_file": "sounds/Analog Snare 1.ogg",
            "image_file": "images/snare/rogers 1964 silver sparkle powertone (cleveland)_thumb.jpg",
            "keyboard_buttons_combination": [
                18
            ],
            "joystick_buttons_combination": [
                1
            ],
            "position_on_screen": {
                "x": 300,
                "y": 100
            },
            "radius": 80
        },
        {
            "name": "Kick",
            "sound_file": "sounds/Analog Kick 1.ogg",
            "image_file": "images/kick/drum-kit-pedal.jpg",
            "keyboard_buttons_combination": [
                7,18
            ],
            "joystick_buttons_combination": [
                2
            ],
            "position_on_screen": {
                "x": 600,
                "y": 100
            },
            "radius": 80
        }
    ]
}
)";

    } // namespace ConfigFile
} // namespace Ion_DrumPad