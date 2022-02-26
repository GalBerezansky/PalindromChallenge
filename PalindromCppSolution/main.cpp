//
//  main.cpp
//  PalindromCppSolution
//
//  Created by Gal Berezansky on 25/02/2022.
//

#include <iostream>
#include <cmath>
#include <arm_acle.h>
#include <vector>

#import <QuartzCore/QuartzCore.h>

std::vector<unsigned long long> pow_10_vector = {};

void intialize_10_pow_vector() {

  unsigned long long value = 1;
  for(unsigned long long i = 0; i < 64; i++) {
    pow_10_vector.push_back(value);
    value *= 10;
  }
}


bool inline trivialIsDecimalPalindrom(const unsigned long long l) {
  unsigned long long reversed = 0;
  for(unsigned long c = l; c > 0 ; c = c / 10)
    reversed = reversed * 10 + c % 10;

  return l == reversed;
}

bool inline failFastIsDecimalPalindrom(const unsigned long long l) {
    const int decimal_length = std::floor(std::log10(l)) + 1;
    int upper_10_pow = decimal_length - 1;
    int lower_10_pow = 1;

    while (lower_10_pow <= upper_10_pow) {
      auto upper_digit = l / pow_10_vector[upper_10_pow] % 10;
      auto lower_digit = l % pow_10_vector[lower_10_pow] / pow_10_vector[lower_10_pow - 1];

      if (upper_digit != lower_digit) {
        return false;
      }

      lower_10_pow += 1;
      upper_10_pow -= 1;
    }

    return true;
}

// This is about 1/4 of 2^32.
__uint128_t trivialCheckThreshold = 1000000000;

static int counter = 2;

inline void printIfDecimalPalindrome(__uint64_t binaryPalindrome) {
  if (failFastIsDecimalPalindrom(binaryPalindrome)) {
    counter += 1;
    std::cout << counter << "\n";
    std::cout << binaryPalindrome << "\n" << std::bitset<64>(binaryPalindrome) << "\n\n";
  }
}

inline void checkSmallPalindromes(__uint32_t num) {
  const int num_length = std::floor(std::log2(num)) + 1;

  __uint32_t reversed_num(__rbit(num));

  __uint64_t reversedLowerHalf = (__uint64_t)reversed_num >> (32 - num_length);
  __uint64_t palindromeToCheck = ((__uint64_t)num << num_length) | reversedLowerHalf;
  printIfDecimalPalindrome(palindromeToCheck);

  palindromeToCheck = ((__uint64_t)num << (num_length + 1)) | reversedLowerHalf;
  printIfDecimalPalindrome(palindromeToCheck);

  palindromeToCheck = palindromeToCheck | (1 << num_length);
  printIfDecimalPalindrome(palindromeToCheck);
}

void find_palindroms() {
  for(__uint32_t i = 1; i < trivialCheckThreshold; i++) {
    checkSmallPalindromes(i);
  }

  for(unsigned long long i = 100000000; i < 1000000000000; i++) {
    const int binary_length = std::floor(std::log2(i)) + 1;

    std::bitset<64> binary_number(i);
    std::bitset<64> reversed_binary(__rbitll(i));

    std::bitset<64> concated_even_length_binary = (binary_number << binary_length) |
                                                  (reversed_binary >> (64 - binary_length));

    std::bitset<64> concated_odd0_length_binary = (binary_number << (binary_length + 1)) |
                                                  (reversed_binary >> (64 - binary_length));

    std::bitset<64> concated_odd1_length_binary = (binary_number << (binary_length + 1)) |
                                                  (one << binary_length) |
                                                  (reversed_binary >> (64 - binary_length));

    if (failFastDecimalPalindrom(concated_even_length_binary.to_ullong())) {
      counter += 1;
      std::cout << counter << "\n";
      std::cout << concated_even_length_binary.to_ullong() << "\n"<< concated_even_length_binary << "\n\n";
    }
    if (failFastDecimalPalindrom(concated_odd0_length_binary.to_ullong())) {
      counter += 1;
      std::cout << counter << "\n";
      std::cout << concated_odd0_length_binary.to_ullong() << "\n"<< concated_odd0_length_binary << "\n\n";
    }
    if (failFastDecimalPalindrom(concated_odd1_length_binary.to_ullong())) {
      counter += 1;
      std::cout << counter << "\n";
      std::cout << concated_odd1_length_binary.to_ullong() << "\n"<< concated_odd1_length_binary << "\n\n";
    }
  }
}

int main(int argc, const char * argv[]) {
  std::cout << 1 << "\n" << 0 << "\n\n" << 2 << "\n" << 1 << "\n\n";

  auto start = CACurrentMediaTime();

  intialize_10_pow_vector();
  find_palindroms();

  auto end = CACurrentMediaTime();
  printf("Time: %f\n", end - start);
  return 0;
}
