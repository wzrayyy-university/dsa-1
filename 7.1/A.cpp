#include <iostream>
#include <string>
#include <vector>

typedef long long ll;

void GrayCode(ll n) {
  if (n <= 0) {
    return;
  }

  std::vector<std::string> code;

  code.push_back("0");
  code.push_back("1");

  ll i, j;

  for (i = 2; i < (1 << n); i = i << 1) {
    for (j = i - 1; j >= 0; j--) {
      code.push_back(code[j]);
    }
    for (j = 0; j < i; j++) {
      code[j] = "0" + code[j];
    }
    for (j = i; j < 2 * i; j++) {
      code[j] = "1" + code[j];
    }
  }

  for (i = 0; i < code.size(); i++)
    std::cout << code[i] << std::endl;
}

int main() {
  ll n;
  std::cin >> n;
  GrayCode(n);
  return 0;
}
