#pragma once

#include <cstdint>
#include <vector>

namespace Ion_DrumPad
{
// sort vector and make it contain only unique entries
void SortMakeUnique(std::vector<uint32_t> &v);

// If vec contains all elements, return a copy of vec without first occurances of elements. Otherwise return empty set. Both 'elements' and 'vec' must be sorted.
std::vector<uint32_t> RemoveSubset(const std::vector<uint32_t> &elements, const std::vector<uint32_t> &vec);
} // namespace Ion_DrumPad
