# Big Fibonacci

Calculates Fibonacci numbers with arbitrary precision. Fast doubling is used as
Fibonacci alforithm which is explanied by [Chun-Min Chang], and Karatsuba
algoritm for multiplication inspired by the [Vladimir Petrigo] implementation
for big numbers.

Arbitrary precision is achieved through a custom [`bigint`] class (only for
positive numbers) with multiplication, addition and subtraction operators
overloaded. Also, the `std::string` conversion operator is overloaded.


## Build

Use the [`Makefile`] file to build the binary. There are some targets available:

 - `release`: The default target generates the optimized binary at `bin/bigfib`.
 - `debug`: Generates the binary for debugging with `gdb`.
 - `clean`: Removes all the compilation files.

Feel free to update the [`CXX`], [`CXXFLAGS`], [`LIBS`] and [`LDFLAGS`]
variables if you need.


## CLI usage

```Text
Usage: bin/bigfib [OPTIONS]... N...
Calculate the Fibonacci number of the given N terms.

  -q, --quiet          don't print the Fibonacci number
  -s, --simple         don't print summary.
  -h, --help           display this help and exit
  -v, --version        output version information and exit
```


## Tests outputs

Outputs for three terms using the quiet options to avoid the Fibonacci number
printing.

```shell
bigfib -q 512 4784969 100000000
```

### [Intel&reg; Core&trade; i5-13420H]

```Text
Term: 512
Chunks: 12
Digits: 107
Calculating time:       0.007045 ms
Casting time:           0.016198 ms
Total time:             0.023243 ms

Term: 4784969
Chunks: 111112
Digits: 1000000
Calculating time:     153.618331 ms
Casting time:           2.326550 ms
Total time:           155.944881 ms

Term: 100000000
Chunks: 2322085
Digits: 20898764
Calculating time:   33070.948792 ms
Casting time:          58.554075 ms
Total time:         33129.502867 ms
```

### [Qualcomm&reg; Snapdragon&trade; 710]

```Text
Term: 512
Chunks: 12
Digits: 107
Calculating time:       0.085416 ms
Casting time:           0.057031 ms
Total time:             0.142447 ms

Term: 4784969
Chunks: 111112
Digits: 1000000
Calculating time:    1033.889999 ms
Casting time:          48.786984 ms
Total time:          1082.676983 ms

Term: 100000000
Chunks: 2322085
Digits: 20898764
Calculating time:  243174.619589 ms
Casting time:         911.000612 ms
Total time:        244085.620201 ms
```


## License

Licensed under [the MIT license][LICENSE].

Share and enjoy!


<!-- References -->

[Chun-Min Chang]: https://chunminchang.github.io/blog/post/calculating-fibonacci-numbers-by-fast-doubling
[Vladimir Petrigo]: https://github.com/vpetrigo/multiplication
[Intel&reg; Core&trade; i5-13420H]: https://www.intel.la/content/www/xl/es/products/sku/232173/intel-core-i513420h-processor-12m-cache-up-to-4-60-ghz/specifications.html
[Qualcomm&reg; Snapdragon&trade; 710]: https://www.qualcomm.com/smartphones/products/7-series/snapdragon-710-mobile-platform
[`bigint`]: src/bigint.hpp
[`Makefile`]: Makefile
[`CXX`]: Makefile#L17
[`CXXFLAGS`]: Makefile#L18
[`LIBS`]: Makefile#L19
[`LDFLAGS`]: Makefile#L20
[LICENSE]: LICENSE
