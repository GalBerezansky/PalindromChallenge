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
#import <Foundation/Foundation.h>

#import "LargeNumbersFinder.h"
#import "SmallNumbersFinder.h"

std::atomic_int counter = 2;

dispatch_group_t find_palindromes_multi_threading() {
  auto group = dispatch_group_create();
  
  NSArray<NSNumber *> *initialValues = @[@1, @2, @3, @4, @5, @6, @7, @8, @9, @(10)];

  for (NSNumber *initialValue in initialValues) {
    dispatch_group_async(group, dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_HIGH, 0), ^{
      for (unsigned long i = initialValue.unsignedLongValue;
           i < smallPalindromesThreshold; i += 10) {
        checkSmallPalindromes(i);
      }

      for (unsigned long i = smallPalindromesThreshold + initialValue.unsignedLongValue;
           i < smallPalindromesThreshold * 2; i += 10) {
        checkLargePalindromes(i, 32);
      }
    });
  }

  return group;
}

void find_palindroms() {
  auto start = CACurrentMediaTime();

  for (unsigned long i = 1; i < smallPalindromesThreshold; ++i) {
    checkSmallPalindromes(i);
  }

  auto end = CACurrentMediaTime();

  std::cout << "Starting large palindromes, time for small palindromes: " << end - start << std::endl;

  // 2533136923 generates the palyndrom 10879740244204797801. (good for sanity checks.  )
  for (unsigned long i = smallPalindromesThreshold; i < smallPalindromesThreshold * 2; ++i) {
    checkLargePalindromes(i, 32);
  }
}

int main(int argc, const char * argv[]) {
  std::cout << 1 << "\n" << 0 << "\n\n" << 2 << "\n" << 1 << "\n\n";

  auto start = CACurrentMediaTime();

  intialize_small_10_pow_vector();
  intialize_large_10_pow_vector();
  auto group = find_palindromes_multi_threading();
  
  dispatch_wait(group, DISPATCH_TIME_FOREVER);

  auto end = CACurrentMediaTime();
  printf("Time: %f\n", end - start);
    
  return 0;
}
