#pragma once

#include "algebra.hpp"

namespace Ion_DrumPad
{
// Defines a drum object
struct Drum
{
    // Uniquely identifying name of a drum. It will be displayed
    std::string name;
    // Path to the sound file
    std::string sound_file;
    // Combination of keys to trigger
    std::vector<uint32_t> keys_combination;
    // Combination of joustick buttons to trigger
    std::vector<uint32_t> joystick_buttons_combination;
    // Position on screen where to draw it
    Position position_on_screen;
};
} // namespace Ion_DrumPad