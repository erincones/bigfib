#ifndef __FIB_HPP_
#define __FIB_HPP_

#include "common.hpp"

#include <vector>
#include <string>


/** Big integer */
typedef std::vector<ull> bigint;


/**
 * Fibonacci class
 */
class Fibonacci {
  private:
    // Private static members

    /** Numeric base */
    static const ull BASE = 1000000000000000000ULL;


    // Private members

    /** Fibonacci number */
    bigint _f;

    /** Fibonacci number as std::string */
    std::string _str;

    /** Calculating time in milliseconds */
    double _calc_ms;

    /** Casting time in milliseconds */
    double _cast_ms;


    // Private methods

    /** Calculate Fibonacci number */
    bigint calc();

    /** Parse Fibonacci number */
    std::string parse();


  public:
    // Public constant members

    /** Fibonacci term */
    const ull n;


    // Public constructors

    // Delete default constructor
    Fibonacci() = delete;

    /**
     * Fibonacci constructor
     *
     * @param n Fibonacci term
     */
    Fibonacci(const ull &n);


    // Public inline getters

    /** Fibonacci number */
    inline const bigint &f() const {
      return this->_f;
    }

    /** Fibonacci number as std::string */
    inline const std::string &str() const {
      return this->_str;
    }

    /** Calculating time in milliseconds */
    inline const double &calc_time() const {
      return this->_calc_ms;
    }

    /** Casting time in milliseconds */
    inline const double &cast_time() const{
      return this->_cast_ms;
    }


    // Public methods

    /**
     * Print fibonacci number information
     *
     * @param summary Print fibonacci number summary
     * @param number Print fibonacci number
     */
    void print(const bool &summary = true, const bool &number = true) const;
};

#endif // __FIB_HPP_
