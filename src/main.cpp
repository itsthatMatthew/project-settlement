/* #include "config.h" */
#include <iostream>
#include <string>

int main(void) {

  std::string operating_system = "Unknown";
  std::string test_msg = "Unknown";
#ifdef SELECTED_OS_TEXT
  operating_system = SELECTED_OS_TEXT;
#endif
#ifdef TEST_MSG
  test_msg = TEST_MSG;
#endif

  std::cout << "Hello developer! You are on " << operating_system << '\n';
  std::cout << "Which is an operating system for a " << test_msg << '\n';
  return 0;
}
