# hilbert

Fast hilbert curve algorithm developed by [rawunprotected](https://github.com/rawrunprotected/hilbert_curves) ported to 64 bit. It includes benchmarks and tests.

| Benchmark          | Time     | CPU   | Iterations
|:------------------:|:--------:|:-----:|:-----------
| BM_XYToIndex/1     | 2 ns     | 2 ns  | 389906979
| BM_XYToIndex/8     | 2 ns     | 2 ns  | 362373234
| BM_XYToIndex/32    | 2 ns     | 2 ns  | 364389751
| BM_IndexToXY/1     | 2 ns     | 2 ns  | 428239325
| BM_IndexToXY/8     | 2 ns     | 2 ns  | 430551968
| BM_IndexToXY/32    | 2 ns     | 2 ns  | 434526211

All the relevant code is in this [header](https://github.com/jbenison/hilbert/blob/master/hilbert/hilbert.h)

A discussion can be found [here](http://threadlocalmutex.com/?p=126).