#include "bigint.hpp"

#include <sstream>
#include <iomanip>
#include <cmath>


// Static private methods

// Naive multiplication
std::vector<ull> bigint::_NAIVE_MULT(const std::vector<ull> &a, const std::vector<ull> &b) {
  std::size_t len = a.size();
  std::vector<ull> r(len << 1ULL);

  std::vector<ull>::const_iterator aend = a.cend();
  std::vector<ull>::const_iterator bend = b.cend();
  std::vector<ull>::const_iterator ai = a.cbegin();
  std::vector<ull>::iterator ri = r.begin();
  std::size_t i = static_cast<std::size_t>(0);

  do {
    std::vector<ull>::const_iterator bi = b.cbegin();
    std::size_t j = static_cast<std::size_t>(0);

    do {
      *(ri + i + j) += *ai * *bi;

      ++bi;
      ++j;
    } while (bi != bend);

    ++ai;
    ++i;
  } while (ai != aend);

  return r;
}

// Karatsuba multiplication
std::vector<ull> bigint::_KARATSUBA_MULT(const std::vector<ull> &a, const std::vector<ull> &b) {
  const std::size_t len = a.size();

  if (len <= static_cast<std::size_t>(32)) {
    return bigint::_NAIVE_MULT(a, b);
  }

  const std::size_t top = len << static_cast<std::size_t>(1);
  const std::size_t mid = len >> static_cast<std::size_t>(1);
  std::vector<ull> r(top);

  const std::vector<ull> ar = std::vector<ull>(a.cbegin(), a.cbegin() + mid);
  const std::vector<ull> al = std::vector<ull>(a.cbegin() + mid, a.end());
  const std::vector<ull> br = std::vector<ull>(b.cbegin(), b.cbegin() + mid);
  const std::vector<ull> bl = std::vector<ull>(b.cbegin() + mid, b.end());

  const std::vector<ull> p1 = bigint::_KARATSUBA_MULT(al, bl);
  const std::vector<ull> p2 = bigint::_KARATSUBA_MULT(ar, br);

  std::vector<ull> alr(mid);
  std::vector<ull> blr(mid);
  const std::vector<ull>::iterator alri = alr.begin();
  const std::vector<ull>::iterator blri = blr.begin();
  const std::vector<ull>::const_iterator ali = al.cbegin();
  const std::vector<ull>::const_iterator ari = ar.cbegin();
  const std::vector<ull>::const_iterator bli = bl.cbegin();
  const std::vector<ull>::const_iterator bri = br.cbegin();

  for (std::size_t i = static_cast<std::size_t>(0); i < mid; ++i) {
    *(alri + i) = *(ali + i) + *(ari + i);
    *(blri + i) = *(bli + i) + *(bri + i);
  }

  std::vector<ull> p3 = bigint::_KARATSUBA_MULT(alr, blr);
  p3.resize(len);

  std::vector<ull>::const_iterator p1i = p1.cbegin();
  std::vector<ull>::const_iterator p2i = p2.cbegin();
  std::vector<ull>::const_iterator p3i = p3.cbegin();
  std::vector<ull>::iterator ri = r.begin();

  for (std::size_t i = static_cast<std::size_t>(0); i < len; ++i, ++p1i, ++p2i, ++p3i, ++ri) {
    *ri = *p2i;
    *(ri + len) = *p1i;
    *(ri + mid) += *p3i - (*p1i + *p2i);
  }

  return r;
}


// Public type conversion operators overloading

// Cast to std::string
bigint::operator std::string() const {
  const std::vector<ull>::const_reverse_iterator rend = this->_data.rend();
  std::vector<ull>::const_reverse_iterator rbegin = this->_data.rbegin();
  std::stringstream dec;

  dec << *rbegin;

  while (++rbegin != rend) {
    dec << std::setfill('0') << std::setw(9) << *rbegin;
  }

  return dec.str();
}


// Public assingment operators overloading

// Direct assignment
bigint &bigint::operator = (const bigint &n) {
  this->_data = n._data;
  return *this;
}


// Public arithmetic operators overloading

// Addition operator
const bigint operator + (const bigint &a, const bigint &b) {
  std::vector<ull> r;
  r.reserve(b._data.size() + static_cast<std::size_t>(1));

  const std::vector<ull>::const_iterator aend = a._data.cend();
  const std::vector<ull>::const_iterator bend = b._data.cend();
  std::vector<ull>::const_iterator ai = a._data.cbegin();
  std::vector<ull>::const_iterator bi = b._data.cbegin();
  ull carry = 0ULL;
  ull c = 0ULL;

  do {
    c = *ai + *bi + carry;

    if (c >= bigint::_BASE) {
      carry = 1ULL;
      c -= bigint::_BASE;
    }
    else {
      carry = 0ULL;
    }

    r.push_back(c);

    ++ai;
    ++bi;
  } while (ai != aend);

  while (bi != bend) {
    c = *bi + carry;

    if (c >= bigint::_BASE) {
      carry = 1ULL;
      c -= bigint::_BASE;
    }
    else {
      carry = 0ULL;
    }

    r.push_back(c);

    ++bi;
  };

  if (carry) {
    r.push_back(1ULL);
  }

  return r;
}

// Subtraction operator
const bigint operator - (const bigint &a, const bigint &b) {
  std::vector<ull> r;
  r.reserve(a._data.size());

  const std::vector<ull>::const_iterator aend = a._data.cend();
  const std::vector<ull>::const_iterator bend = b._data.cend();
  std::vector<ull>::const_iterator ai = a._data.cbegin();
  std::vector<ull>::const_iterator bi = b._data.cbegin();
  ull carry = 0ULL;
  ull c = 0ULL;

  do {
    c = *ai - *bi - carry;

    if (c >= bigint::_BASE) {
      carry = 1ULL;
      c += bigint::_BASE;
    }
    else {
      carry = 0ULL;
    }

    r.push_back(c);

    ++ai;
    ++bi;
  } while (bi != bend);

  while (ai != aend) {
    c = *ai - carry;

    if (c >= bigint::_BASE) {
      carry = 1ULL;
      c += bigint::_BASE;
    }
    else {
      carry = 0ULL;
    }

    r.push_back(c);

    ++ai;
  }

  return r;
}

// Multiplication operator
const bigint operator * (const bigint &a, const bigint &b) {
  std::vector<ull> x(a._data);
  std::vector<ull> y(b._data);
  std::size_t len = std::max(x.size(), y.size());
  std::size_t extra = static_cast<std::size_t>(1);

  while (len & (len - extra)) {
    ++len;
  }

  x.resize(len);
  y.resize(len);

  std::vector<ull> r = bigint::_KARATSUBA_MULT(x, y);
  std::vector<ull>::const_iterator rend = r.cend() - extra;
  std::vector<ull>::iterator ri = r.begin();

  do {
    *(ri + extra) += *ri / bigint::_BASE;
    *ri %= bigint::_BASE;
    ++ri;
  } while (ri != rend);

  if (*ri >= bigint::_BASE) {
    *(ri + extra) += *ri / bigint::_BASE;
    *ri %= bigint::_BASE;
  }

  extra = static_cast<std::size_t>(0);
  for (std::vector<ull>::const_reverse_iterator i = r.crbegin(); *i == 0ULL; ++i, ++extra);

  if (extra != static_cast<std::size_t>(0)) {
    r.resize(r.size() > extra ? r.size() - extra : static_cast<std::size_t>(1));
  }

  return r;
}
