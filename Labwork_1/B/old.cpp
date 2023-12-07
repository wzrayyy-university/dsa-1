#include <iostream>
#include <vector>

int main() {
    int length;
    long offset;

    std::vector<int> numbers;
    std::vector<int> new_numbers;

    std::cin >> length >> offset;

    if (offset > 0)
        offset %= length;
    else if (offset < 0)
        offset = -((-offset) % length);

    numbers.resize(length);
    new_numbers.resize(length);

    for (int i = 0; i < length; i++) {
        std::cin >> numbers[i];
    }
    new_numbers = numbers;

    if (offset > 0) {
        for (int i = offset; i < length + offset; i++) {
            new_numbers[i % length] = numbers[i-offset];
        }
    } else if (offset < 0) {
        for (int i = -offset; i < length - offset; i++) {
            new_numbers[i+offset] = numbers[i % length];
        }
    }

    for (int i = 0; i < length; i++) {
        std::cout << new_numbers[i] << " ";
    }
}