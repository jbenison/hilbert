#include <hilbert/hilbert.h>
#include <test/test_helper.h>
#include <benchmark/benchmark.h>

static void BM_XYToIndex(benchmark::State &state)
{
    uint64_t n, idx;
    n = static_cast<uint64_t>(state.range_x());
    auto xy = random_xy(n);
    while (state.KeepRunning()) {
        idx = hilbertXYToIndex(n, xy.first, xy.second);
    }
}
BENCHMARK(BM_XYToIndex)->Range(1, 32);

static void BM_IndexToXY(benchmark::State &state)
{
    uint64_t n, idx, x, y;
    n = static_cast<uint64_t>(state.range_x());
    idx = random_idx(n);
    while (state.KeepRunning()) {
        hilbertIndexToXY(n, idx, x, y);
    }
}
BENCHMARK(BM_IndexToXY)->Range(1, 32);

BENCHMARK_MAIN();
