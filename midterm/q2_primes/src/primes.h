#ifndef MIDTERM_PRIME_H
#define MIDTERM_PRIME_H

#include <vector>

//===================================================================
// TODO: Write specification for generate_primes
//===================================================================
/**
* Finds all primes included from 1 to n-1
* @param n the amount of numbers to search starting from 0
* @return a vector of prime numbers that are included 
*/
std::vector<int> generate_primes (int n);

/**
 * Finds a value within the supplied vector of integers
 * @param data vector to search
 * @param val value to find
 * @return the index of the FIRST occurrence of the value val in data
 *         or -1 if not found
 */
int binary_search(const std::vector<int>& data, int val);

/**
 * Checks if a positive integer is prime (up to 2^31-1)
 * @param n integer to check, must satisfy 0 < n <= 2^31-1
 * @return true if number is prime, false otherwise
 */
bool is_prime(int n);

#endif //MIDTERM_PRIME_H
