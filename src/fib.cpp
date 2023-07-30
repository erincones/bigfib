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
  bigint a(1, 0ULL);

  if (n == 0ULL) return a;

  bigint b(1, 1ULL);

  for (ull i = 1ULL; i < n; ++i) {
    const bigint::const_iterator aend = a.end();
    bigint::iterator ai = a.begin();
    bigint::iterator bi = b.begin();
    ull carry = 0ULL;

    do {
      ull c = *ai + *bi + carry;

      if (c >= BASE) {
        carry = 1ULL;
        c -= Fibonacci::BASE;
      }
      else {
        carry = 0ULL;
      }

      *ai = *bi;
      *bi = c;

      ++ai;
      ++bi;
    } while (ai != aend);

    if (bi != b.end()) {
      a.push_back(*bi);
      *bi += carry;
    }
    else if (carry) {
      b.push_back(carry);
    }
  }

  return b;
}

// Calculate Fibonacci number
std::string Fibonacci::parse() {
  const bigint::const_reverse_iterator rend = this->_f.rend();
  bigint::const_reverse_iterator rbegin = this->_f.rbegin();
  std::stringstream dec;

  dec << *rbegin;

  while (++rbegin != rend) {
    dec << std::setfill('0') << std::setw(18) << *rbegin;
  }

  return dec.str();
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
  this->_str = this->parse();
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
      << "Chunks: " << this->_f.size()
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
};
