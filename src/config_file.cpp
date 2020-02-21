#include "config_file.hpp"

#include <string>
#include <vector>
#include <stdexcept>
#include <fstream>

#include "algebra.hpp"
#include "drum.hpp"
#include <nlohmann/json.hpp>

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
    j.at("key_combination").get_to(d.keys_combination);
    j.at("joystick_buttons_combination").get_to(d.joystick_buttons_combination);
    j.at("position_on_screen").get_to(d.position_on_screen);
}

std::vector<Drum> Ion_DrumPad::ConfigFile::ReadFromFile(std::string file)
{
    std::ifstream ifs(file);
    json js = json::parse(ifs);
    std::vector<Drum> drums;
    for (auto &entry : js)
    {
        // drums.emplace_back(entry["name"].get<std::string>(),
        //                    entry["sound_file"].get<std::string>(),
        //                    entry["key_combination"].get<std::vector<uint32_t>>(),
        //                    entry["joystick_buttons_combination"].get<std::vector<uint32_t>>(),
        //                    entry["position_on_screen"].get<Position>();
        drums.emplace_back(entry.get<Drum>());
    }
    Validate(drums);
    return drums;
}
} // namespace Ion_DrumPad