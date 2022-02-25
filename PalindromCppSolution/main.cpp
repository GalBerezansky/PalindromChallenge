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

bool inline failFastDecimalPalindrom(const unsigned long long l) {
    const int decimal_length = std::floor(std::log10(l)) + 1;
    int upper_10_pow = decimal_length - 1;
    int lower_10_pow = 1;

    while(lower_10_pow <= upper_10_pow) {
      auto upper_digit = l / pow_10_vector[upper_10_pow] % 10;
      auto lower_digit = l % pow_10_vector[lower_10_pow] / pow_10_vector[lower_10_pow - 1] ;

      if (upper_digit != lower_digit) {
        return false;
      }

      lower_10_pow += 1;
      upper_10_pow -= 1;
    }

    return true;
}

void find_palindroms() {
  int counter = 0;

  counter += 1;
  std::cout << counter << "\n";
  std::cout << 0 << "\n"<< 0 << "\n\n";

  counter += 1;
  std::cout << counter << "\n";
  std::cout << 1 << "\n"<< 1 << "\n\n";
  std::bitset<128> one(1);

  for(__uint128_t i = 1; i < 100000000; i++) {
    const int binary_length = std::floor(std::log2(i)) + 1;

    std::bitset<128> binary_number(i);
    std::bitset<128> reversed_binary(__rbitll(i));

    std::bitset<128> concated_even_length_binary = (binary_number << binary_length) |
                                                  (reversed_binary >> (64 - binary_length));

    std::bitset<128> concated_odd0_length_binary = (binary_number << (binary_length + 1)) |
                                                  (reversed_binary >> (64 - binary_length));

    std::bitset<128> concated_odd1_length_binary = (binary_number << (binary_length + 1)) |
                                                  (one << binary_length) |
                                                  (reversed_binary >> (64 - binary_length));

    if (trivialIsDecimalPalindrom(concated_even_length_binary.to_ullong())) {
      counter += 1;
      std::cout << counter << "\n";
      std::cout << concated_even_length_binary.to_ullong() << "\n"<< concated_even_length_binary << "\n\n";
    }
    if (trivialIsDecimalPalindrom(concated_odd0_length_binary.to_ullong())) {
      counter += 1;
      std::cout << counter << "\n";
      std::cout << concated_odd0_length_binary.to_ullong() << "\n"<< concated_odd0_length_binary << "\n\n";
    }
    if (trivialIsDecimalPalindrom(concated_odd1_length_binary.to_ullong())) {
      counter += 1;
      std::cout << counter << "\n";
      std::cout << concated_odd1_length_binary.to_ullong() << "\n"<< concated_odd1_length_binary << "\n\n";
    }
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
  intialize_10_pow_vector();
  find_palindroms();
  return 0;
}
