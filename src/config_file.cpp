#include "config_file.hpp"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <filesystem>

#include <nlohmann/json.hpp>

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
        j.at("rgb").get_to(d.rgb);
    }

    void from_json(const json &j, Title &t)
    {
        j.at("text").get_to(t.text);
        j.at("rgb").get_to(t.rgb);
    }

    void from_json(const json &j, Dimensions &d)
    {
        j.at("width").get_to(d.width);
        j.at("height").get_to(d.height);
    }

    namespace ConfigFile
    {
        void from_json(const json &j, ConfigFile::Config &c)
        {
            c.window_size = j["window_size"];
            c.title = j["title"];
            for (auto &js_drum : j["drums"])
            {
#ifdef DEBUG
                std::cout << js_drum << "\n";
#endif
                c.drums.emplace_back(js_drum.get<Drum>());
            }
        }

        Config::Config(const std::string &file)
        {
            std::ifstream ifs(file);
            auto fpath = std::filesystem::absolute(file);
            std::cout << "Loading config file: " << fpath.string() << std::endl;
            if (!ifs.is_open())
            {
                if (std::filesystem::exists(file))
                {
                    std::cout << "Failed to load config file." << std::endl;
                    throw std::runtime_error("File does not exist: " + fpath.string());
                }
                else
                {
                    std::cout << "Failed to load config file." << std::endl;
                    throw std::runtime_error("Could not open file: " + fpath.string());
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
    "window_size":
    {
        "width": 1024,
        "height": 768
    },
    "title":
    {
        "text": "Ion Audio IED08 Drum Rocker for PlayStation binding",
        "rgb": [0, 111, 205]
    },
    "drums": [
        {
            "name": "HiHat",
            "sound_file": "sounds/Analog Hihat 1.ogg",
            "image_file": "images/hihat/drum-kit-hi-hat.jpg",
            "keyboard_buttons_combination": [7],
            "joystick_buttons_combination": [3,11,107],
            "position_on_screen": {"x": 200,"y": 150},
            "radius": 80,
            "rgb": [255,255,0]
        },
        {
            "name": "Snare",
            "sound_file": "sounds/Analog Snare 1.ogg",
            "image_file": "images/snare/rogers 1964 silver sparkle powertone (cleveland)_thumb.jpg",
            "keyboard_buttons_combination": [18],
            "joystick_buttons_combination": [2,10],
            "position_on_screen": {"x": 100,"y": 350},
            "radius": 80,
            "rgb": [255,0,0]
        },
        {
            "name": "Tom-tom1",
            "sound_file": "sounds/General Room Hi Tom.ogg",
            "image_file": "images/tom/drum-kit-1488406125CbG.jpg",
            "keyboard_buttons_combination": [999],
            "joystick_buttons_combination": [3,10],
            "position_on_screen": {"x": 300,"y": 300},
            "radius": 80,
            "rgb": [255,255,0]
        },
        {
            "name": "Tom-tom2",
            "sound_file": "sounds/General Room Mid Tom.ogg",
            "image_file": "images/tom/drum-kit-1488406125CbG.jpg",
            "keyboard_buttons_combination": [999],
            "joystick_buttons_combination": [0,10],
            "position_on_screen": {"x": 500,"y": 300},
            "radius": 80,
            "rgb": [0,0,255]
        },
        {
            "name": "Tom-tom3",
            "sound_file": "sounds/General Room Low Tom.ogg",
            "image_file": "images/tom/drum-kit-1488406125CbG.jpg",
            "keyboard_buttons_combination": [999],
            "joystick_buttons_combination": [1,10],
            "position_on_screen": {"x": 700,"y": 350},
            "radius": 80,
            "rgb": [0,255,0]
        },
        {
            "name": "Crash",
            "sound_file": "sounds/General Crash.ogg",
            "image_file": "images/cymbal/320px-Bellotti_Cymbal.jfif",
            "keyboard_buttons_combination": [999],
            "joystick_buttons_combination": [1,11,107],
            "position_on_screen": {"x": 600,"y": 150},
            "radius": 80,
            "rgb": [0,255,0]
        },
        {
            "name": "Ride",
            "sound_file": "sounds/General Ride.ogg",
            "image_file": "images/cymbal/320px-Bellotti_Cymbal.jfif",
            "keyboard_buttons_combination": [999],
            "joystick_buttons_combination": [0,11,107],
            "position_on_screen": {"x": 400,"y": 100},
            "radius": 80,
            "rgb": [0,0,255]
        },
        {
            "name": "Kick",
            "sound_file": "sounds/Analog Kick 1.ogg",
            "image_file": "images/kick/drum-kit-pedal.jpg",
            "keyboard_buttons_combination": [7,18],
            "joystick_buttons_combination": [4],
            "position_on_screen": {"x": 400,"y": 500},
            "radius": 80,
            "rgb": [255,128,0]
        }
    ]
}
)";

    } // namespace ConfigFile
} // namespace Ion_DrumPad