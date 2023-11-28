#include "fib.hpp"
#include "ui.hpp"


/**
 * Main function
 *
 * @param argc Number of arguments
 * @param argv Array of arguments
 * @return Exit status
*/
int main(const int argc, const char *const *const argv) {
  UI ui(argc, argv);
  const int status = ui.process();
  return status;
}
