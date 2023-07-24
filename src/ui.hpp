#ifndef __UI_HPP_
#define __UI_HPP_

#include "common.hpp"

#include <vector>
#include <string>


/**
 * User interface class
 */
class UI {
  private:
    // Private structs

    /** Argument struct */
    struct arg {
      /** Fibonacci term */
      const char *const n;

      /** Print Fibonacci number */
      bool print_number;

      /** Print summary */
      bool print_summary;

      /** Unknown options */
      std::vector<const char *> unknown;
    };


    // Private constant members

    /** Binary name */
    const char *const _bin;


    // Private members

    /** Show help */
    bool _help;

    /** Show version */
    bool _version;

    /** Arguments list */
    std::vector<arg> _args;


    // Private methods

    /** Display error message */
    void _print_error() const;

    /** Display help message */
    void _print_help() const;

    /** Display version message */
    void _print_version() const;


  public:
    // Public constructors

    // Delete default constructor
    UI() = delete;

    /**
     * User interface constructor
     *
     * @param argc Number of arguments
     * @param argv Array of arguments
     */
    UI(const int &argc, const char *const *const argv);


    // Public methods

    /** Process arguments */
    int process() const;
};

#endif // __UI_HPP_
