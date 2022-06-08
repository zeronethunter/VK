#include <cassert>
#include <iostream>

void input_data(unsigned int &n, unsigned int &k) {  // input n, k variables
  std::cin >> n;
  std::cin >> k;
  assert((k >= 0 && k <= 31));
}

unsigned int solve(unsigned int n, unsigned int k) {  // solving...
  if ((1 << k) & n) {      // check bit on the k position
    return n & ~(1 << k);  // 00011001 & 11101111 -> 00001011 (inverse if k-bit
                           // is one)
  } else {
    return n | (1 << k);  // 00011001 | 00000010 -> 00011011 (inverse if k-bit
                          // is zero)
  }
}

int main() {
  unsigned int n, k;
  input_data(n, k);

  std::cout << solve(n, k) << std::endl;

  return 0;
}
