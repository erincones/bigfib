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


## License

Licensed under [the MIT license][LICENSE].

Share and enjoy!


<!-- References -->

[Chun-Min Chang]: https://chunminchang.github.io/blog/post/calculating-fibonacci-numbers-by-fast-doubling
[Vladimir Petrigo]: https://github.com/vpetrigo/multiplication
[`bigint`]: src/bigint.hpp
[`Makefile`]: Makefile
[`CXX`]: Makefile#L17
[`CXXFLAGS`]: Makefile#L18
[`LIBS`]: Makefile#L19
[`LDFLAGS`]: Makefile#L20
[LICENSE]: LICENSE
