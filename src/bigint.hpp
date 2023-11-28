#ifndef __BIGINT_HPP_
#define __BIGINT_HPP_

#include <vector>
#include <string>


/** Unsigned long long int */
typedef unsigned long long int ull;


/**
 * Big integer class
 */
class bigint {
  private:
    // Private static members

    /** Numeric base */
    static const ull _BASE = 1000000000ULL;


    // Private static methods

    /**
     * Naive multiplication
     *
     * @param a Multiplier
     * @param a Multiplicand
     * @return Multiplication product
     */
    static std::vector<ull> _NAIVE_MULT(const std::vector<ull> &a, const std::vector<ull> &b);

    /**
     * Karatsuba multiplication
     *
     * @param a Multiplier
     * @param a Multiplicand
     * @return Multiplication product
     */
    static std::vector<ull> _KARATSUBA_MULT(const std::vector<ull> &a, const std::vector<ull> &b);


    // Private members

    /** Number data */
    std::vector<ull> _data;


    // Private constructors

    /**
     * Big integer constructor from std::vector
     *
     * @param n Initializator
    */
    inline bigint(const std::vector<ull> n) : _data(n) {};


  public:
    // Public constructors

    /**
     * Default constructor
     */
    inline bigint() : _data(static_cast<std::size_t>(1), 0ULL) {};

    /**
     * Big integer copy constructor
     *
     * @param n Number to copy
     */
    inline bigint(const bigint &n) : _data(n._data) {};

    /**
     * Big integer constructor from unsigned long long less than the
     * `bigint::_BASE`
     *
     * @param n Initializator
     */
    inline bigint(const ull &n) : _data(static_cast<std::size_t>(1), n) {};


    // Constant getters

    /**
     * Get the number of chunks
     *
     * @return Number of memory chunks
     */
    inline std::size_t chunks() const {
      return this->_data.size();
    }


    // Public type conversion operators overloading

    /** Cast to std::string */
    operator std::string() const;


    // Public assingment operators overloading

    /** Direct assignment */
    bigint &operator = (const bigint &n);


    // Public arithmetic operators overloading

    /**
     * Addition operator
     *
     * @param a Augend
     * @param b Addend
     * @return Addition sum
     */
    friend const bigint operator + (const bigint &a, const bigint &b);

    /**
     * Subtraction operator without extra zeroes removing
     *
     * @param a Minuend
     * @param b Subtrahend
     * @return Subtraction difference
     */
    friend const bigint operator - (const bigint &a, const bigint &b);

    /**
     * Multiplication operator
     *
     * @param a Multiplier
     * @param b Multiplicand
     * @return Multiplication product
     */
    friend const bigint operator * (const bigint &a, const bigint &b);

    /**
     * Standard output
     *
     * @param stream Output stream
     * @param n Number to output
     * @return The same output stream
     */
    friend inline std::ostream &operator << (std::ostream &stream, const bigint &n) {
      stream << std::string(n);
      return stream;
    }
};

#endif // __BIGINT_HPP_
