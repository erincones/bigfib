#ifndef __FIB_HPP_
#define __FIB_HPP_

#include "bigint.hpp"


/**
 * Fibonacci class
 */
class Fibonacci {
  private:
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

    /**
     * Get the fibonacci number
     *
     * @return Fibonacci number
     */
    inline const bigint &f() const {
      return this->_f;
    }

    /**
     * Get the calculating time in milliseconds
     *
     * @return Calculating time in milliseconds
     */
    inline const double &calc_time() const {
      return this->_calc_ms;
    }

    /**
     * Get the casting time in milliseconds
     *
     * @return Casting time in milliseconds
     */
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
