#include "fib.hpp"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <chrono>


/** Get current clock time */
#define NOW std::chrono::high_resolution_clock::now

/** Calculate duration in milliseconds */
#define DURATION std::chrono::duration<double, std::milli>

/** Format double */
#define FORMAT std::fixed << std::setw(14)


/** Time point */
typedef std::chrono::high_resolution_clock::time_point time_point;


// Private methods

// Calculate Fibonacci number
bigint Fibonacci::calc() {
  if (n == 0ULL) {
    return 0ULL;
  }
  else if (n < 3ULL) {
    return 1ULL;
  }

  ull h = 0ULL;
  bigint a = 0ULL;
  bigint b = 1ULL;

  for (ull i = n; i; ++h, i >>= 1ULL);

  for (ull m = 1ULL << (h - 1ULL); m; m >>= 1ULL) {
    bigint c = a * (b + b - a);
    bigint d = a * a + b * b;

    if (n & m) {
      a = d;
      b = c + d;
    }
    else {
      a = c;
      b = d;
    }
  }

  return a;
}


// Public constructors

// Fibonacci constructor
Fibonacci::Fibonacci(const ull &n) : _calc_ms(-1.0), _cast_ms(-1.0), n(n) {
  time_point start;
  time_point stop;

  start = NOW();
  this->_f = this->calc();
  stop = NOW();
  this->_calc_ms = DURATION(stop - start).count();

  start = NOW();
  this->_str = std::string(this->_f);
  stop = NOW();
  this->_cast_ms = DURATION(stop - start).count();
}


// Methods

// Print fibonacci number information
void Fibonacci::print(const bool &summary, const bool &number) const {
  double cout_ms = 0.0;

  if (number) {
    const time_point start = NOW();
    std::cout << this->_str << std::endl;
    const time_point stop = NOW();
    cout_ms = DURATION(stop - start).count();
  }

  if (summary) {
    std::cout
      << "Term: " << this->n
      << std::endl
      << "Chunks: " << this->_f.chunks()
      << std::endl
      << "Digits: " << this->_str.size()
      << std::endl
      << "Calculating time: " << FORMAT << this->_calc_ms << " ms"
      << std::endl
      << "Casting time:     " << FORMAT << this->_cast_ms << " ms"
      << std::endl;

    if (number) {
      std::cout
        << "Printing time:    " << FORMAT << cout_ms << " ms"
        << std::endl;
    }

    std::cout
      << "Total time:       " << FORMAT << this->_calc_ms + this->_cast_ms + cout_ms << " ms"
      << std::endl;
  }
}
