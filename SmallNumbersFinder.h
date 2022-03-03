//
//  LargeNumbersFinderMultiThread.h
//  PalindromCppSolution
//
//  Created by Ben Yohay on 01/03/2022.
//

#ifndef LargeNumbersFinderMultiThread_h
#define LargeNumbersFinderMultiThread_h

std::vector<unsigned long long> small_pow_10_vector = {};

std::vector<unsigned long long> small_palindromes_vecotr = { 0, 1 };

void intialize_small_10_pow_vector() {
  // 10^20 doesn't fit into 2^64, so we go until 10^19.
  unsigned long long value = 1;
  for(unsigned long long i = 0; i < 20; i++) {
    small_pow_10_vector.push_back(value);
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
      auto upper_digit = l / small_pow_10_vector[upper_10_pow] % 10;
      auto lower_digit = l % small_pow_10_vector[lower_10_pow] / small_pow_10_vector[lower_10_pow - 1];

      if (upper_digit != lower_digit) {
        return false;
      }

      lower_10_pow += 1;
      upper_10_pow -= 1;
    }

    return true;
}

// This was chosen because the resulting palindrome is contained in 2^64 for small numbers, and the
// 2^31 concatenated with itself and adding one bit can be at most 2^63 bits.
unsigned long smallPalindromesThreshold = ((unsigned long)1) << 31;

extern std::atomic_int counter;

inline void printIfDecimalPalindrome(__uint64_t binaryPalindrome) {
  if (failFastIsDecimalPalindrom(binaryPalindrome)) {
    small_palindromes_vecotr.push_back(binaryPalindrome);
  }
}

inline void checkSmallPalindromes(const unsigned long num) {
  const int num_length = std::floor(std::log2(num)) + 1;

  unsigned long reversed_num(__rbitll(num) >> 32);

  __uint64_t reversedLowerHalf = (__uint64_t)reversed_num >> (32 - num_length);
  __uint64_t palindromeToCheck = ((__uint64_t)num << num_length) | reversedLowerHalf;
  printIfDecimalPalindrome(palindromeToCheck);

  palindromeToCheck = ((__uint64_t)num << (num_length + 1)) | reversedLowerHalf;
  printIfDecimalPalindrome(palindromeToCheck);

  palindromeToCheck = palindromeToCheck | ((__uint64_t)1 << num_length);
  printIfDecimalPalindrome(palindromeToCheck);
}

#endif /* LargeNumbersFinderMultiThread_h */
