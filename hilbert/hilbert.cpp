#include <hilbert/hilbert.h>
#include <cstdint>

namespace {

uint64_t deinterleave(uint64_t x)
{
    x = x & 0x5555555555555555;
    x = (x | (x >> 1)) & 0x3333333333333333;
    x = (x | (x >> 2)) & 0x0F0F0F0F0F0F0F0F;
    x = (x | (x >> 4)) & 0x00FF00FF00FF00FF;
    x = (x | (x >> 8)) & 0x0000FFFF0000FFFF;
    x = (x | (x >> 16)) & 0x00000000FFFFFFFF;
    return x;
}

uint64_t interleave(uint64_t x)
{
    x = (x | (x << 16)) & 0x0000FFFF0000FFFF;
    x = (x | (x << 8)) & 0x00FF00FF00FF00FF;
    x = (x | (x << 4)) & 0x0F0F0F0F0F0F0F0F;
    x = (x | (x << 2)) & 0x3333333333333333;
    x = (x | (x << 1)) & 0x5555555555555555;
    return x;
}

uint64_t prefixScan(uint64_t x)
{
    x = (x >> 16) ^ x;
    x = (x >> 8) ^ x;
    x = (x >> 4) ^ x;
    x = (x >> 2) ^ x;
    x = (x >> 1) ^ x;
    return x;
}

}

void hilbertIndexToXY(uint64_t n, uint64_t i, uint64_t& x, uint64_t& y)
{
    i = i << (64 - 2 * n);

    uint64_t i0 = deinterleave(i);
    uint64_t i1 = deinterleave(i >> 1);

    uint64_t t0 = (i0 | i1) ^ 0xFFFFFFFF;
    uint64_t t1 = i0 & i1;

    uint64_t prefixT0 = prefixScan(t0);
    uint64_t prefixT1 = prefixScan(t1);

    uint64_t a = (((i0 ^ 0xFFFFFFFF) & prefixT1) | (i0 & prefixT0));

    x = (a ^ i1) >> (32 - n);
    y = (a ^ i0 ^ i1) >> (32 - n);
}

uint64_t hilbertXYToIndex(uint64_t n, uint64_t x, uint64_t y)
{
    x = x << (32 - n);
    y = y << (32 - n);

    uint64_t A, B, C, D;

    // Initial prefix scan round, prime with x and y
    {
        uint64_t a = x ^ y;
        uint64_t b = 0xFFFFFFFF ^ a;
        uint64_t c = 0xFFFFFFFF ^ (x | y);
        uint64_t d = x & (y ^ 0xFFFFFFFF);

        A = a | (b >> 1);
        B = (a >> 1) ^ a;

        C = ((c >> 1) ^ (b & (d >> 1))) ^ c;
        D = ((a & (c >> 1)) ^ (d >> 1)) ^ d;
    }

    {
        uint64_t a = A;
        uint64_t b = B;
        uint64_t c = C;
        uint64_t d = D;

        A = ((a & (a >> 2)) ^ (b & (b >> 2)));
        B = ((a & (b >> 2)) ^ (b & ((a ^ b) >> 2)));

        C ^= ((a & (c >> 2)) ^ (b & (d >> 2)));
        D ^= ((b & (c >> 2)) ^ ((a ^ b) & (d >> 2)));
    }

    {
        uint64_t a = A;
        uint64_t b = B;
        uint64_t c = C;
        uint64_t d = D;

        A = ((a & (a >> 4)) ^ (b & (b >> 4)));
        B = ((a & (b >> 4)) ^ (b & ((a ^ b) >> 4)));

        C ^= ((a & (c >> 4)) ^ (b & (d >> 4)));
        D ^= ((b & (c >> 4)) ^ ((a ^ b) & (d >> 4)));
    }

    {
        uint64_t a = A;
        uint64_t b = B;
        uint64_t c = C;
        uint64_t d = D;

        A = ((a & (a >> 8)) ^ (b & (b >> 8)));
        B = ((a & (b >> 8)) ^ (b & ((a ^ b) >> 8)));

        C ^= ((a & (c >> 8)) ^ (b & (d >> 8)));
        D ^= ((b & (c >> 8)) ^ ((a ^ b) & (d >> 8)));
    }

    // Final round and projection
    {
        uint64_t a = A;
        uint64_t b = B;
        uint64_t c = C;
        uint64_t d = D;

        C ^= ((a & (c >> 16)) ^ (b & (d >> 16)));
        D ^= ((b & (c >> 16)) ^ ((a ^ b) & (d >> 16)));
    }

    // Undo transformation prefix scan
    uint64_t a = C ^ (C >> 1);
    uint64_t b = D ^ (D >> 1);

    // Recover index bits
    uint64_t i0 = x ^ y;
    uint64_t i1 = b | (0xFFFFFFFF ^ (i0 | a));

    return ((interleave(i1) << 1) | interleave(i0)) >> (64 - 2 * n);
}
