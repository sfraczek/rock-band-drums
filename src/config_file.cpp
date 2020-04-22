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
// Checks if data is correct
void Validate(std::vector<Drum> drums)
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

// void to_json(json &j, const Drum &p)
// {
//     j = json{{"name", p.name}, {"address", p.address}, {"age", p.age}};
// }

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

std::vector<Drum> Ion_DrumPad::ConfigFile::ReadFromFile(std::string file)
{
    std::ifstream ifs(file);
    if (!ifs.is_open()) {
        std::filesystem::path fpath(file);
        std::string to_append = fpath.string() + " in path: " + std::filesystem::current_path().string();
        if (std::filesystem::exists(file)) {
            throw std::runtime_error("File does not exist: " + to_append);
        }
        else
        {
            throw std::runtime_error("Could not open file: " + to_append);
        }
    }
    json js_drum_list = json::parse(ifs);
    std::vector<Drum> drums;
    for (auto &js_drum : js_drum_list)
    {
        std::cout << js_drum << "\n";
        drums.emplace_back(js_drum.get<Drum>());
    }
    Validate(drums);
    return drums;
}
} // namespace Ion_DrumPad