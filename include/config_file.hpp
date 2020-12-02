#pragma once

#include <string>
#include <vector>

#include "algebra.hpp"
#include "title.hpp"
#include "drum.hpp"

namespace Ion_DrumPad
{

    // Object holding configuration file
    namespace ConfigFile
    {
        struct Config
        {
            // Reads config from file and calls Validate and initializes members
            Config(const std::string &file);
            // Checks if data is correct
            void Validate();
            Dimensions window_size;
            Title title;
            std::vector<Drum> drums;
        };

        // Raw string with default config file content
        extern const char *default_config;
    } // namespace ConfigFile
} // namespace Ion_DrumPad
