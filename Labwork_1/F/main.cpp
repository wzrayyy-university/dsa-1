#include <iostream>

int main() {
    int n;
    std::cin >> n;

    int *days = new int[n];
    int *sums_lr = new int[n];
    int *sums_rl = new int[n];

    for (int i = 0; i < n; ++i) {
        std::cin >> days[i];
        sums_lr[i] = 0;
        sums_rl[i] = 0;
    }

    for (int i = 1; i < n; ++i) {
        sums_lr[i] = sums_lr[i-1] + days[i-1];
    }

    for (int i = n-2; i > -1; --i) {
        sums_rl[i] = sums_rl[i+1] + days[i+1];
    }

    for (int i = 0; i < n; ++i) {
        if (sums_rl[i] == sums_lr[i]) {
            std::cout << i;
            return 0;
        }
    }

    std::cout << -1;
    return 0;
}