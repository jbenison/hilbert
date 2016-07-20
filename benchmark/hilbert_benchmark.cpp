#include <hilbert/hilbert.h>
#include <test/test_helper.h>
#include <benchmark/benchmark.h>
#include <iostream>

std::uint64_t index;

static void BM_XYToIndex(benchmark::State &state)
{
    std::uint64_t n = static_cast<uint64_t>(state.range_x());
    std::pair<std::uint64_t, std::uint64_t> xy = random_xy(n);
    while (state.KeepRunning()) {
        benchmark::DoNotOptimize(index = hilbert::xy_to_index(n, xy.first, xy.second));
    }
    //std::cout << index << "\n";
}
BENCHMARK(BM_XYToIndex)->Range(1, 32);

std::pair<std::uint64_t, std::uint64_t> xy_pair;

static void BM_IndexToXY(benchmark::State &state)
{
    uint64_t n, idx;
    n = static_cast<uint64_t>(state.range_x());
    idx = random_idx(n);
    while (state.KeepRunning()) {
        benchmark::DoNotOptimize(xy_pair = hilbert::index_to_xy(n, idx));
    }
    //std::cout << xy_pair.first << ", " << xy_pair.second << "\n";
}
BENCHMARK(BM_IndexToXY)->Range(1, 32);

BENCHMARK_MAIN();
