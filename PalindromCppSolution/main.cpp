//
//  main.cpp
//  PalindromCppSolution
//
//  Created by Gal Berezansky on 25/02/2022.
//

#include <iostream>
#include <cmath>
#include <arm_acle.h>


bool isDecimalPalindrom(const unsigned long long l) {
  unsigned long long reversed = 0;
  for(unsigned long c = l; c > 0 ; c=c/10)
    reversed = reversed * 10 + c % 10;
  return l == reversed;
}

void find_palindroms() {
  int counter = 0;

  counter += 1;
  std::cout << counter << "\n";
  std::cout << 0 << "\n"<< 0 << "\n\n";

  counter += 1;
  std::cout << counter << "\n";
  std::cout << 1 << "\n"<< 1 << "\n\n";

  for(unsigned long long i = 1; i < 1000000000000000; i++) {
    const int binary_length = std::floor(std::log2(i)) + 1;

    std::bitset<64> binary_number(i);
    std::bitset<64> reversed_binary(__rbitll(i));

    std::bitset<64> concated_even_length_binary = (binary_number << binary_length) |
                                                  (reversed_binary >> (64 - binary_length));

    std::bitset<64> concated_odd0_length_binary = (binary_number << (binary_length + 1)) |
                                                  (reversed_binary >> (64 - binary_length));

    std::bitset<64> one(1);
    std::bitset<64> concated_odd1_length_binary = (binary_number << (binary_length + 1)) |
                                                  (one << binary_length) |
                                                  (reversed_binary >> (64 - binary_length));

    if (isDecimalPalindrom(concated_even_length_binary.to_ullong())) {
      counter += 1;
      std::cout << counter << "\n";
      std::cout << concated_even_length_binary.to_ullong() << "\n"<< concated_even_length_binary << "\n\n";
    }
    if (isDecimalPalindrom(concated_odd0_length_binary.to_ullong())) {
      counter += 1;
      std::cout << counter << "\n";
      std::cout << concated_odd0_length_binary.to_ullong() << "\n"<< concated_odd0_length_binary << "\n\n";
    }
    if (isDecimalPalindrom(concated_odd1_length_binary.to_ullong())) {
      counter += 1;
      std::cout << counter << "\n";
      std::cout << concated_odd1_length_binary.to_ullong() << "\n"<< concated_odd1_length_binary << "\n\n";
    }
  }
}

int main(int argc, const char * argv[]) {
  find_palindroms();
//  isDecimalPalindrom(12321);
  return 0;
}

