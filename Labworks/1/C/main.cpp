#include <iostream>
#include <cmath>

int get_mcd(int a, int b) {
   if (b == 0) 
      return a;
   return get_mcd(b, a % b);
}

int main() {
    int a, b;
    std::cin >> a >> b;
    std::cout << get_mcd(a, b);
    return 0;
}