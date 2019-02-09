#include "primes.h"
#include "TestException.h"

#include <chrono>
#include <iostream>

namespace std {
/**
 * Helper function for printing vector of integers useful for test results
 * @param data vector to print
 * @return stringified version of vector
 */
std::string to_string(const std::vector<int> &data) {
  std::string out = "{";
  bool first = true;
  for (const auto &i : data) {
    if (!first) {
      out.append(", ");
    }
    out.append(std::to_string(i));
    first = false;
  }
  out.append("}");
  return out;
}
} // std

/**
 * Tests if the set of generate_primes(n) matches what is expected
 * @param n argument for generate_primes
 * @param expected expected set of primes
 * @throws TestException if the test fails
 */
void test_generate_primes(int n, const std::vector<int>& expected) {
  // generate primes
  auto primes = generate_primes(n);

  // check if match
  if (primes != expected) {
    std::string msg = "generate_primes failed.";
    // only print if < 50 primes
    if (primes.size() < 50 && expected.size() < 50) {
      msg.append("\n  ");
      msg.append(std::to_string(primes));
      msg.append("\n  ");
      msg.append(std::to_string(expected));
    }
    throw TestException(msg);
  }
}

/**
 * Unit Tests for generate_primes
 * @throws TestException if a unit test fails
 */
void test_generate_primes() {

  //===================================================================
  // TODO: Test generate_primes to figure out what exactly it does
  //===================================================================
  test_generate_primes(10, {2, 3, 5, 7});
  test_generate_primes(1, {});
  test_generate_primes(30, { 2,3,5,7,11,13,17,19,23,29 });
  test_generate_primes(5, {2,3});

}

/**
 * Tests binary_search to see if the result is what is expected
 * @param data vector to search for element
 * @param val value to search for within vector
 * @param expected expected result of search
 */
void test_binary_search(const std::vector<int>& data, int val, int expected) {

  int idx = binary_search(data, val);
  if (idx != expected) {
    std::string msg = "binary_search failed for input: \n";
    msg.append("  {");
    msg.append(std::to_string(data));
    msg.append(", ");
    msg.append(std::to_string(val));
    msg.append("\n");
    msg.append("  ");
    msg.append(std::to_string(idx));
    msg.append(" vs expected ");
    msg.append(std::to_string(expected));
    throw TestException(msg);
  }
}

/**
 * Unit Tests for binary_search
 * @throws TestException if a test fails
 */
void test_binary_search() {

  //===================================================================
  // TODO: Implement unit tests for binary_search
  //===================================================================
  // single element found

  test_binary_search({0, 1, 2, 3, 4, 5}, 2, 2);
  //check whether function works with extra 0 in front
  test_binary_search({0,1,2,3,4,5,0006,7,8,9},6 ,6 );
  // longer vector
  test_binary_search({ 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30 },24,24);
  //large numbers
  test_binary_search({ 100000,100001,100002,100003,100004,100005 }, 100002, 2);
  //all the same in vector
  test_binary_search({ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, 1, 0);
  //not existing
  test_binary_search({ 1,2,3,4,5 }, 0, -2);



}


/**
 * Tests is_prime(n) to see if it produces expected result
 * @param n integer to check if prime
 * @param expected prime (true) or not prime (false)
 * @throws TestException if test fails
 */
void test_is_prime(int n, bool expected) {

  bool prime = is_prime(n);
  if (prime != expected) {
    std::string msg = "is_prime failed for input: ";
    msg.append(std::to_string(n));
    msg.append(", expected ");
    if (expected) {
      msg.append("true");
    } else {
      msg.append("false");
    }
    throw TestException(msg);
  }
}

/**
 * Unit tests for is_prime
 * @throws TestException if a unit test fails
 */
void test_is_prime() {

  //===================================================================
  // TODO: Implement unit tests for is_prime
  //===================================================================
  // small prime
  test_is_prime(11, true);
  // large number that is not prime
  test_is_prime(100000000, false);
  // large number that is prime
  test_is_prime(1500450271, true);
  // 2 is even but prime
  test_is_prime(2, true);
  // 1 is not prime
  test_is_prime(1, false);



}

/**
 * Runs all unit tests
 * @return 0 if completed successfully, negative if unit tests fail
 */
int main() {

  int out = 0;

  try {
    test_generate_primes();
  } catch (TestException& ex) {
    std::cerr << ex.what() << std::endl;
    --out;
  }
  std::cin.get();
  try {
    test_binary_search();
  } catch (TestException& ex) {
    std::cerr << ex.what() << std::endl;
    --out;
  }

  std::cin.get();

  try {
    test_is_prime();
  } catch (TestException& ex) {
    std::cerr << ex.what() << std::endl;
    --out;
  }

  std::cin.get();

  if (out == 0) {
    std::cout << "All tests passed!" << std::endl;
  }

  return out;
}
