#include "ui.hpp"
#include "fib.hpp"

#include <iostream>
#include <cstring>


// Private methods

// Display error message
void UI::_print_error() const {
  std::cerr
    << this->_bin << ": Missing arguments."
    << std::endl
    << "Try '" << this->_bin << " --help' for more information."
    << std::endl;
}

// Display help message
void UI::_print_help() const {
  std::cout
    << "Usage: " << this->_bin << " {[OPTIONS] N}..."
    << std::endl
    << "Calculate the Fibonacci number of the given N terms."
    << std::endl << std::endl
    << "  -q, --quiet          don't print the Fibonacci number"
    << std::endl
    << "  -s, --simple         don't print summary."
    << std::endl
    << "  -h, --help           display this help and exit"
    << std::endl
    << "  -v, --version        output version information and exit"
    << std::endl;
}

// Display version message
void UI::_print_version() const {
  std::cout
    << this->_bin << " " << VERSION
    << std::endl
    << "Copyright (C) 2023 Erick Rincones."
    << std::endl
    << "Licensed under The MIT License."
    << std::endl
    << "This is free software: you are free to change and redistribute it."
    << std::endl
    << "There is NO WARRANTY, to the extent permitted by law."
    << std::endl << std::endl
    << "Written by Erick Rincones."
    << std::endl;
}


// Public constructors

// User interface constructor
UI::UI(const int &argc, const char *const *const argv) :
_bin(argv[0]),
_help(false),
_version(false) {
  bool print_number = true;
  bool print_summary = true;
  std::vector<const char *> unknown;

  for (int i = 1; i < argc; ++i) {
    const char *const curr = argv[i];

    if (!std::strcmp(curr, "-h") || !std::strcmp(curr, "--help")) {
      this->_help = true;
      break;
    }
    if (!std::strcmp(curr, "-v") || !std::strcmp(curr, "--version")) {
      this->_version = true;
      break;
    }

    if (!std::strcmp(curr, "-q") || !std::strcmp(curr, "--quiet")) {
      print_number = false;
    }
    else if (!std::strcmp(curr, "-s") || !std::strcmp(curr, "--simple")) {
      print_summary = false;
    }
    else if (curr[0] == '-') {
      unknown.push_back(curr);
    }
    else {
      this->_args.push_back({
        curr,
        print_number,
        print_summary,
        unknown
      });

      print_number = true;
      print_summary = true;
      unknown.clear();
    }
  }
}


// Public methods

// Process arguments
int UI::process() const {
  if (this->_help) {
    this->_print_help();
    return EXIT_SUCCESS;
  }

  if (this->_version) {
    this->_print_version();
    return EXIT_SUCCESS;
  }

  if (this->_args.size() == 0) {
    this->_print_error();
    return EXIT_FAILURE;
  }

  for (const UI::arg &curr : this->_args) {
    try {
      Fibonacci(std::stoull(curr.n)).print(curr.print_summary, curr.print_number);

      for (const char *const str : curr.unknown) {
        std::cerr << "Error. Unknown argument: \"" << str << "\"" << std::endl;
      }
    }
    catch (const std::invalid_argument &err) {
      std::cerr << "Error. Not valid number: \"" << curr.n << "\"" << std::endl;
    }
    catch (const std::exception &err) {
      std::cerr << "Error. Unknown." << std::endl;
    }
  }

  return EXIT_SUCCESS;
}
