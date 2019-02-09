#include "word_count.h"
#include <exception>
#include <iostream>

// Exception class to throw for unit test failures
class UnitTestException : public std::exception {
  std::string line_;
  int start_idx_;
  int result_;
  int expected_;

 public:

  // constructor collecting all information
  UnitTestException(const std::string& line, int start_idx,
                    int result, int expected) : line_(line), start_idx_(start_idx),
                                                result_(result), expected_(expected) {}

  const char* what() {
    return "Unit test failed";
  }

  std::string info() {
    std::string out;
    out.append("line: ");
    out.append(line_);
    out.append(", start_idx: ");
    out.append(std::to_string(start_idx_));
    out.append(", result: ");
    out.append(std::to_string(result_));
    out.append(", expected: ");
    out.append(std::to_string(expected_));
    return out;
  }

};


/**
 * Tests word_count for the given line and starting index
 * @param line line in which to search for words
 * @param start_idx starting index in line to search for words
 * @param expected expected answer
 * @throws UnitTestException if the test fails
 */
void wc_tester(const std::string& line, int start_idx, int expected) {

  int result = word_count(line, start_idx);

  // if not what we expect, throw an error
  if (result != expected) {
    throw UnitTestException(line, start_idx, result, expected);
  }

}

int main() {

  try {


    // YOUR TESTS HERE
    wc_tester("hello world",0,2);
    wc_tester(" hello world",1,2);
    wc_tester("hello    world", 0, 2);
    wc_tester("hello world     ",0,2);
	wc_tester("in the loveliest town of all, where the houses were white and high and the elms trees were green and higher than the houses, where the front yards were wide and pleasant and the back yards were bushy and worth finding out about, where the streets sloped down to the stream and the stream flowed quietly under the bridge, where the lawns ended in orchards and the orchards ended in fields and the fields ended in pastures and the pastures climbed the hill and disappeared over the top toward the wonderful wide sky, in this loveliest of all towns Stuart stopped to get a drink of sarsaparilla",0,107);

  } catch(UnitTestException &ute) {
    std::cout << ute.info() << std::endl;
  }
  std::cout << "it works! yeah!" << std::endl;
  std::cin.get();
}
