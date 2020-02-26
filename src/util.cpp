#include "util.hpp"

#include <algorithm>

void Ion_DrumPad::sort_make_unique(std::vector<uint32_t> &v)
{
    std::sort(v.begin(), v.end());
    auto ep = std::unique(v.begin(), v.end());
    v.resize(std::distance(v.begin(), ep));
}