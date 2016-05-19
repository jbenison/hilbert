# hilbert

This is an obscene fast hilbert curve algorithm developed
by [rawunprotected](https://github.com/rawrunprotected/hilbert_curves) that I have ported to 64 bit and added
benchmarks and tests.

| Benchmark          | Time      | CPU    | Iterations
|:------------------:|:---------:|:------:|:-----------
| BM_XYToIndex/1     | 17 ns     | 17 ns  | 38198556
| BM_XYToIndex/8     | 17 ns     | 17 ns  | 41009057
| BM_XYToIndex/32    | 17 ns     | 17 ns  | 40985046
| BM_IndexToXY/1     | 12 ns     | 12 ns  | 59275819
| BM_IndexToXY/8     | 12 ns     | 12 ns  | 59964364
| BM_IndexToXY/32    | 12 ns     | 12 ns  | 59845939
