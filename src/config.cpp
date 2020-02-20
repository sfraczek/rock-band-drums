#include "lib.hpp"

#include <vector>

void Ion_DrumPad::Config::Validate()
{
    for (size_t i = 0; i < drums.size(); i++)
    {
        for (size_t j = 0; j < drums.size(); j++)
        {
            if (i != j && drums[i].name == drums[j].name)
                throw std::invalid_argument("Repeated drum name '" drums[i].name + "' encountered in the config. Drum names must be unique.");
        }
    }
}