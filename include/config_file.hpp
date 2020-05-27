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
std::vector<Drum> ReadFromFile(const std::string& file);

// Raw string with default config file content
extern const char* default_config;
} // namespace ConfigFile
} // namespace Ion_DrumPad
