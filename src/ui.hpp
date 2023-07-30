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
    // Private constant members

    /** Binary name */
    const char *const _bin;


    // Private members

    /** Show help */
    bool _show_help;

    /** Show version */
    bool _show_version;

    /** Print Fibonacci numbers */
    bool _print_number;

    /** Print summary */
    bool _print_summary;

    /** Fibonacci terms */
    std::vector<const char *> _n;

    /** Unknown options */
    std::vector<const char *> _unknown;


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
