#include "util.hpp"

#include <algorithm>

void Ion_DrumPad::SortMakeUnique(std::vector<uint32_t> &v)
{
    std::sort(v.begin(), v.end());
    auto ep = std::unique(v.begin(), v.end());
    v.resize(std::distance(v.begin(), ep));
}

std::optional<std::vector<uint32_t>> Ion_DrumPad::RemoveSubset(const std::vector<uint32_t> &elements, const std::vector<uint32_t> &vec)
{
    std::vector<uint32_t> new_set;
    auto vec_it = vec.begin();
    auto el_it = elements.begin();
    while (el_it != elements.end())
    {
        if (vec_it == vec.end())
            return std::nullopt;
        if (*vec_it == *el_it)
        {
            ++el_it;
        }
        else
        {
            new_set.push_back(*vec_it);
        }
        ++vec_it;
    }
    std::copy(vec_it, vec.end(), back_inserter(new_set));
    return new_set;
}
