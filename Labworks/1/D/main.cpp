#include <iostream>


int main() {
    int n, m, q, counter = 0;
    std::cin >> n >> m >> q;
    bool** episodes = new bool* [n];
    for (int i = 0; i < n; ++i) {
        episodes[i] = new bool[m];
    }

    for (int i = 0; i < q; ++i) {
        int e, s;
        std::cin >> e >> s;

        if (!episodes[s - 1][e - 1]) {
            episodes[s - 1][e - 1] = true;
            ++counter;
        }
    }

    std::cout << n*m - counter << "\n";

    for (int s = 0; s < n; ++s) {
        for (int e = 0; e < m; ++e) {
            if (!episodes[s][e]) {
                std::cout << e + 1 << " " << s + 1 << "\n";
            }
        }
    }
    delete[] episodes;
    return 0;
}