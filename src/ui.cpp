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
    << "Usage: " << this->_bin << " [OPTIONS]... N..."
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
_show_help(false),
_show_version(false),
_print_number(true),
_print_summary(true) {
  for (int i = 1; i < argc; ++i) {
    const char *const curr = argv[i];

    if (!std::strcmp(curr, "-h") || !std::strcmp(curr, "--help")) {
      this->_show_help = true;
      return;
    }
    if (!std::strcmp(curr, "-v") || !std::strcmp(curr, "--version")) {
      this->_show_version = true;
      return;
    }

    if (!std::strcmp(curr, "-q") || !std::strcmp(curr, "--quiet")) {
      this->_print_number = false;
    }
    else if (!std::strcmp(curr, "-s") || !std::strcmp(curr, "--simple")) {
      this->_print_summary = false;
    }
    else if (curr[0] == '-') {
      this->_unknown.push_back(curr);
    }
    else {
      do {
        this->_n.push_back(argv[i]);
      } while (++i < argc);
      return;
    }
  }
}


// Public methods

// Process arguments
int UI::process() const {
  if (this->_show_help) {
    this->_print_help();
    return EXIT_SUCCESS;
  }

  if (this->_show_version) {
    this->_print_version();
    return EXIT_SUCCESS;
  }

  for (const char *const &str : this->_unknown) {
    std::cerr << "Error. Unknown argument: \"" << str << "\"" << std::endl;
  }

  if (this->_n.size() == 0) {
    this->_print_error();
    return EXIT_FAILURE;
  }

  if (!this->_print_summary && !this->_print_number) {
    std::cout << "Warning. Nothing is printed if the -q and -s options are specified at the same time." << std::endl;
    return EXIT_SUCCESS;
  }

  const char *const &last = this->_n.back();

  for (const char *const &n : this->_n) {
    try {
      Fibonacci(std::stoull(n)).print(this->_print_summary, this->_print_number);
      if (&n != &last) {
        std::cout << std::endl;
      }
    }
    catch (const std::invalid_argument &err) {
      std::cerr << "Error. Not valid number: \"" << n << "\"" << std::endl;
    }
    catch (const std::exception &err) {
      std::cerr << "Error. Unknown." << std::endl;
    }
  }

  return EXIT_SUCCESS;
}
