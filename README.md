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

 - `release`: The default target generates de optimized binary at `bin/bigfib`.
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

### [AMD Ryzen&trade; 7 5700U]

```Text
Term: 512
Chunks: 12
Digits: 107
Calculating time:       0.013195 ms
Casting time:           0.015670 ms
Total time:             0.028865 ms

Term: 4784969
Chunks: 111112
Digits: 1000000
Calculating time:     220.479498 ms
Casting time:           3.840622 ms
Total time:           224.320120 ms

Term: 100000000
Chunks: 2322085
Digits: 20898764
Calculating time:   52460.604902 ms
Casting time:          76.934597 ms
Total time:         52537.539499 ms
```

### [Intel&reg; Core&trade; i5-13420H]

```Text
Term: 512
Chunks: 12
Digits: 107
Calculating time:       0.010548 ms
Casting time:           0.002362 ms
Total time:             0.012910 ms

Term: 4784969
Chunks: 111112
Digits: 1000000
Calculating time:     181.037429 ms
Casting time:           2.739238 ms
Total time:           183.776667 ms

Term: 100000000
Chunks: 2322085
Digits: 20898764
Calculating time:   39561.871474 ms
Casting time:          54.250652 ms
Total time:         39616.122126 ms
```


## License

Licensed under [the MIT license][LICENSE].

Share and enjoy!


<!-- References -->

[Chun-Min Chang]: https://chunminchang.github.io/blog/post/calculating-fibonacci-numbers-by-fast-doubling
[Vladimir Petrigo]: https://github.com/vpetrigo/multiplication
[AMD Ryzen&trade; 7 5700U]: https://www.amd.com/en/products/apu/amd-ryzen-7-5700u
[Intel&reg; Core&trade; i5-13420H]: https://www.intel.la/content/www/xl/es/products/sku/232173/intel-core-i513420h-processor-12m-cache-up-to-4-60-ghz/specifications.html
[`bigint`]: src/bigint.hpp
[`Makefile`]: Makefile
[`CXX`]: Makefile#L17
[`CXXFLAGS`]: Makefile#L18
[`LIBS`]: Makefile#L19
[`LDFLAGS`]: Makefile#L20
[LICENSE]: LICENSE
