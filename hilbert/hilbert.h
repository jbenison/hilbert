#ifndef HILBERT_H
#define HILBERT_H

#include <cstdint>
#include <utility>

namespace hilbert {

namespace detail {

std::uint64_t bit_unzip(std::uint64_t x)
{
    x = x & 0x5555555555555555;
    x = (x | (x >> 1)) & 0x3333333333333333;
    x = (x | (x >> 2)) & 0x0F0F0F0F0F0F0F0F;
    x = (x | (x >> 4)) & 0x00FF00FF00FF00FF;
    x = (x | (x >> 8)) & 0x0000FFFF0000FFFF;
    x = (x | (x >> 16)) & 0x00000000FFFFFFFF;

    return x;
};

std::uint64_t prefix_scan(std::uint64_t x)
{
    x = (x >> 16) ^ x;
    x = (x >> 8) ^ x;
    x = (x >> 4) ^ x;
    x = (x >> 2) ^ x;
    x = (x >> 1) ^ x;

    return x;
};

}

std::pair<std::uint64_t, std::uint64_t> index_to_xy(std::uint64_t n, std::uint64_t i)
{
    i = i << (64 - 2 * n);

    std::uint64_t i0 = detail::bit_unzip(i);
    std::uint64_t i1 = detail::bit_unzip(i >> 1);

    std::uint64_t t0 = (i0 | i1) ^ 0xFFFFFFFF;
    std::uint64_t t1 = i0 & i1;

    std::uint64_t prefix_t0 = detail::prefix_scan(t0);
    std::uint64_t prefix_t1 = detail::prefix_scan(t1);

    std::uint64_t a = (((i0 ^ 0xFFFFFFFF) & prefix_t1) | (i0 & prefix_t0));

    std::uint64_t x = (a ^ i1) >> (32 - n);
    std::uint64_t y = (a ^ i0 ^ i1) >> (32 - n);

    return std::make_pair(x, y);
}

namespace detail {

std::uint64_t bit_zip(std::uint64_t x)
{
    x = (x | (x << 16)) & 0x0000FFFF0000FFFF;
    x = (x | (x << 8)) & 0x00FF00FF00FF00FF;
    x = (x | (x << 4)) & 0x0F0F0F0F0F0F0F0F;
    x = (x | (x << 2)) & 0x3333333333333333;
    x = (x | (x << 1)) & 0x5555555555555555;

    return x;
};

}

std::uint64_t xy_to_index(std::uint64_t n, std::uint64_t x, std::uint64_t y)
{
    x = x << (32 - n);
    y = y << (32 - n);

    std::uint64_t A, B, C, D;

    {
        std::uint64_t a = x ^ y;
        std::uint64_t b = 0xFFFFFFFF ^ a;
        std::uint64_t c = 0xFFFFFFFF ^ (x | y);
        std::uint64_t d = x & (y ^ 0xFFFFFFFF);

        A = a | (b >> 1);
        B = (a >> 1) ^ a;

        C = ((c >> 1) ^ (b & (d >> 1))) ^ c;
        D = ((a & (c >> 1)) ^ (d >> 1)) ^ d;
    }

    {
        std::uint64_t a = A;
        std::uint64_t b = B;
        std::uint64_t c = C;
        std::uint64_t d = D;

        A = ((a & (a >> 2)) ^ (b & (b >> 2)));
        B = ((a & (b >> 2)) ^ (b & ((a ^ b) >> 2)));

        C ^= ((a & (c >> 2)) ^ (b & (d >> 2)));
        D ^= ((b & (c >> 2)) ^ ((a ^ b) & (d >> 2)));
    }

    {
        std::uint64_t a = A;
        std::uint64_t b = B;
        std::uint64_t c = C;
        std::uint64_t d = D;

        A = ((a & (a >> 4)) ^ (b & (b >> 4)));
        B = ((a & (b >> 4)) ^ (b & ((a ^ b) >> 4)));

        C ^= ((a & (c >> 4)) ^ (b & (d >> 4)));
        D ^= ((b & (c >> 4)) ^ ((a ^ b) & (d >> 4)));
    }

    {
        std::uint64_t a = A;
        std::uint64_t b = B;
        std::uint64_t c = C;
        std::uint64_t d = D;

        A = ((a & (a >> 8)) ^ (b & (b >> 8)));
        B = ((a & (b >> 8)) ^ (b & ((a ^ b) >> 8)));

        C ^= ((a & (c >> 8)) ^ (b & (d >> 8)));
        D ^= ((b & (c >> 8)) ^ ((a ^ b) & (d >> 8)));
    }

    {
        std::uint64_t a = A;
        std::uint64_t b = B;
        std::uint64_t c = C;
        std::uint64_t d = D;

        C ^= ((a & (c >> 16)) ^ (b & (d >> 16)));
        D ^= ((b & (c >> 16)) ^ ((a ^ b) & (d >> 16)));
    }

    std::uint64_t a = C ^ (C >> 1);
    std::uint64_t b = D ^ (D >> 1);

    std::uint64_t i0 = x ^ y;
    std::uint64_t i1 = b | (0xFFFFFFFF ^ (i0 | a));

    return ((detail::bit_zip(i1) << 1) | detail::bit_zip(i0)) >> (64 - 2 * n);
}

}

#endif
