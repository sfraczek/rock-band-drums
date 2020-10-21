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
    // Path to the image file
    std::string image_file;
    // Combination of keys to trigger
    std::vector<uint32_t> keyboard_buttons_combination;
    // Combination of joustick buttons to trigger
    std::vector<uint32_t> joystick_buttons_combination;
    // Position on screen where to draw it
    Position position_on_screen;
    // radius of drawn button
    float radius;
    // RGB(A-optional) color components
    std::vector<uint8_t> rgb;
};
} // namespace Ion_DrumPad