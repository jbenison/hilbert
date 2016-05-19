#ifndef HILBERT_TEST_HELPER
#define HILBERT_TEST_HELPER

#include <cassert>
#include <limits>
#include <random>
#include <utility>

// Valid Hilbert curve level has a mathematical limitation.
// Maximum level is (number of bits)/2 or (number of bytes) * 4.
template <typename T>
inline bool valid_level(T n)
{
    static_assert(std::is_unsigned<T>::value, "Level must be unsigned");
    return n <= (sizeof(T) * 4);
}

// Return the maximum possible position index value for the given level n
template <typename T>
inline T max_idx(T n)
{
    // T will overflow by one bit during calculation when n == half
    // the number of bits in T
    if (n == (sizeof(T) * 4))
        return std::numeric_limits<T>::max();
    return n << 2 - 1;
}

// Return the maximum possible x, y coordinate values for the given level n
template <typename T>
inline T max_xy(T n)
{
    return n << 1 - 1;
}

// Helper function to generate a random number between zero and n
template <typename T>
inline T random(T n) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<T> dis(0, n);

    return dis(gen);
};

// Generates a random hilbert position index that is valid for
// the given level n
template <typename T>
T random_idx(T n)
{
    assert(valid_level(n));
    return random(max_idx(n));
};

// Generates a random x, y coordinate pair that is valid for
// the given level n
template <typename T>
std::pair<T, T> random_xy(T n)
{
    assert(valid_level(n));
    return std::move(std::make_pair(random(max_xy(n)), random(max_xy(n))));
};

#endif
