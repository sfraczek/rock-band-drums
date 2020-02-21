#pragma once

#include <string>
#include <vector>

#include "drum.hpp"

namespace Ion_DrumPad
{
// Manages configuration file
namespace ConfigFile
{
// Reads config from file and calls Validate returns drums configuration
std::vector<Drum> ReadFromFile(std::string file);
} // namespace ConfigFile
} // namespace Ion_DrumPad
