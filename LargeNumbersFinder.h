//
//  LargeNumbersFinder.hpp
//  PalindromCppSolution
//
//  Created by Ben Yohay on 26/02/2022.
//

#ifndef LargeNumbersFinder_hpp
#define LargeNumbersFinder_hpp

#include <iostream>
#include <cmath>
#include <arm_acle.h>
#include <vector>

#import <QuartzCore/QuartzCore.h>

void intialize_large_10_pow_vector();

std::vector<__uint128_t> large_pow_10_vector = {};

extern std::atomic_int counter;

void intialize_large_10_pow_vector() {
  // 10^39 doesn't fit into 2^128, so we go until 10^38.
  __uint128_t value = 1;
  for(__uint128_t i = 0; i < 39; i++) {
    large_pow_10_vector.push_back(value);
    value *= 10;
  }
}

inline bool failFastIsDecimalPalindromLarge(const __uint128_t l) {
    const int decimal_length = std::floor(std::log10(l)) + 1;
    int upper_10_pow = decimal_length - 1;
    int lower_10_pow = 1;

    while (lower_10_pow <= upper_10_pow) {
      auto upper_digit = l / large_pow_10_vector[upper_10_pow] % 10;
      auto lower_digit = l % large_pow_10_vector[lower_10_pow] / large_pow_10_vector[lower_10_pow - 1];

      if (upper_digit != lower_digit) {
        return false;
      }

      lower_10_pow += 1;
      upper_10_pow -= 1;
    }

    return true;
}

std::string toString(__uint128_t num) {
    std::string str;
    do {
        int digit = num % 10;
        str = std::to_string(digit) + str;
        num = (num - digit) / 10;
    } while (num != 0);
    return str;
}

inline void print128BitsNumber(const __uint128_t num) {
  std::cout << toString(num) << std::endl << std::bitset<128>(num) << std::endl;
}

inline void printIfDecimalPalindromeLarge(const unsigned long originalNum,
                                          const __uint128_t binaryPalindrome) {
  if (failFastIsDecimalPalindromLarge(binaryPalindrome)) {
    counter += 1;
    std::cout << counter << std::endl;
    print128BitsNumber(binaryPalindrome);
    std::cout << "original number:" << originalNum << std::endl << std::endl;
  }
}

inline void checkLargePalindromes(const unsigned long num, const unsigned int num_length) {
  __uint128_t reversedLowerHalf = (__uint128_t)__rbitll(num) >> (64 - num_length);
  __uint128_t palindromeToCheck = ((__uint128_t)num << num_length) | reversedLowerHalf;
  printIfDecimalPalindromeLarge(num, palindromeToCheck);

  palindromeToCheck = ((__uint128_t)num << (num_length + 1)) | reversedLowerHalf;
  printIfDecimalPalindromeLarge(num, palindromeToCheck);

  palindromeToCheck = palindromeToCheck | ((__uint128_t)1 << num_length);
  printIfDecimalPalindromeLarge(num, palindromeToCheck);
}

#endif /* LargeNumbersFinder_hpp */
