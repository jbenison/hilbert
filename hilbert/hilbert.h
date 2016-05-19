#ifndef HILBERT_H
#define HILBERT_H

#include <cstdint>

// Converts a 2d xy grid coordinate to a 1d hilbert curve index.
uint64_t hilbertXYToIndex(uint64_t n, uint64_t x, uint64_t y);

// Converts a 1d hilbert curve index to 2d xy grid coordinates.
void hilbertIndexToXY(uint64_t n, uint64_t i, uint64_t& x, uint64_t& y);

#endif
