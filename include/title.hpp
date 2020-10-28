#pragma once

namespace Ion_DrumPad
{
// Defines a title object
struct Title
{
    // Title to be displayed of binding identifying name of a drum set. It will be displayed
    std::string text;
    // RGB(A-optional) color components
    std::vector<uint8_t> rgb;
};
} // namespace Ion_DrumPad