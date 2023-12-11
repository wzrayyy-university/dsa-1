#include <iostream>

int main() {
    int size, offset_l = 0, offset_r = 0, counter = 0;

    std::cin >> size;

    char *word = new char[size];
    for (int i = 0; i < size; ++i)
        std::cin >> word[i];

    if (size == 3) {
        if (word[0] == word[1] || word[1] == word[2] || word[0] == word[2])
            std::cout << "YES";
        else
            std::cout << "NO";
        return 0;
    }

    for (int i = 0; i < (size / 2) + (size % 2) - counter; ++i) {
        if (word[i + offset_l] != word[size - i - offset_r - 1]) {
            ++counter;
            if (word[i + offset_l + 1] == word[size - i - offset_r - 1])
                ++offset_l;
            else
                ++offset_r;
        }
    }
    delete[] word;

    if (counter < 2)
        std::cout << "YES";
    else
        std::cout << "NO";
    return 0;
}
