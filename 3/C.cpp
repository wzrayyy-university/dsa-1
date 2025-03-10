#include <iostream>

typedef long long ll;

void RadixSort(char** arr, const ll size, const ll offset) {
  if (size == 1)
    return;

  int i, j, idx;
  idx = 0;
  i = idx;
  j = 1;

  while (idx < size) {
    while (arr[i][offset] > arr[j][offset]) {
      std::swap(arr[i], arr[j]);
      if (i == 0)
        break;
      --j;
      --i;
    }
    i = idx;
    j = ++idx;
  }
}

int main() {
  ll messages_size, message_length, max_offset;

  std::cin >> messages_size >> message_length >> max_offset;

  char** messages = new char* [messages_size];

  for (ll i = 0; i < messages_size; ++i) {
    messages[i] = new char[message_length];
    for (ll j = 0; j < message_length; ++j){
      std::cin >> messages[i][j];
    }
  }

  for (ll offset = message_length - 1; message_length - offset - 1 < max_offset; --offset) {
    RadixSort(messages, messages_size, offset);
  }

  for (ll i = 0; i < messages_size; ++i) {
    std::cout << messages[i] << '\n';
  }
  return 0;
}
