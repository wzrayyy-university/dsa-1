#include <iostream>

int* CalculateCriticScore(const int* critics, int** movies, int critics_count, int movie_count);
void Merge(int* arr, int* indexes, int left, int mid, int right);
void MergeSort(int* arr, int* indexes, int start, int end);

void Merge(int* arr, int* indexes, int left, int mid, int right) {
  int left_size = mid - left + 1;
  int right_size = right - mid;

  int* left_arr = new int[left_size];
  int* right_arr = new int[right_size];

  int* left_idxs = new int[left_size];
  int* right_idxs = new int[right_size];

  for (int i = 0; i < left_size; ++i) {
    left_arr[i] = arr[left + i];
    left_idxs[i] = indexes[left + i];
  }

  for (int i = 0; i < right_size; ++i) {
    right_arr[i] = arr[mid + 1 + i];
    right_idxs[i] = indexes[mid + 1 + i];
  }

  int i = 0, j = 0, idx = left;

  while (i < left_size && j < right_size) {
    if (left_arr[i] >= right_arr[j]) {
      arr[idx] = left_arr[i];
      indexes[idx] = left_idxs[i];
      ++i;
    } else {
      arr[idx] = right_arr[j];
      indexes[idx] = right_idxs[j];
      ++j;
    }
    ++idx;
  }

  while (i < left_size) {
    arr[idx] = left_arr[i];
    indexes[idx] = left_idxs[i];
    ++i;
    ++idx;
  }

  while (j < right_size) {
    arr[idx] = right_arr[j];
    indexes[idx] = right_idxs[j];
    ++j;
    ++idx;
  }

  delete[] left_idxs;
  delete[] right_idxs;
  delete[] left_arr;
  delete[] right_arr;
}

void MergeSort(int* arr, int* indexes, int start, int end) { // NOLINT(*-no-recursion)
  if (start >= end)
    return;

  int mid = start + (end - start) / 2;
  MergeSort(arr, indexes, start, mid);
  MergeSort(arr, indexes, mid + 1, end);

  Merge(arr, indexes, start, mid, end);
}

int* CalculateCriticScore(const int* critics, int** movies, int critics_count, int movie_count) {
  int* scores = new int[movie_count];
  int* indexes = new int[movie_count];
  for (int i = 0; i < movie_count; ++i) {
    scores[i] = 0;
    indexes[i] = i + 1;
    long long vote;
    for (int j = 0; j < critics_count; ++j) {
      vote = static_cast<long long>(movies[i][j]) * static_cast<long long>(critics[j]);
      scores[i] = (static_cast<long long>(scores[i]) + vote) % 1000000007LL;
    }
  }

  MergeSort(scores, indexes, 0, movie_count - 1);

  delete[] scores;
  return indexes;
}

int main() {
  int critics_count, movie_count, rating_count;
  std::cin >> critics_count >> movie_count >> rating_count;

  int* critics = new int[critics_count];
  for (int i = 0; i < critics_count; ++i) {
    std::cin >> critics[i];
  }

  int** movies = new int* [movie_count];
  for (int i = 0; i < movie_count; ++i) {
    movies[i] = new int[critics_count];
    for (int j = 0; j < critics_count; ++j) {
      std::cin >> movies[i][j];
    }
  }

  int* indexes = CalculateCriticScore(critics, movies, critics_count, movie_count);
  for (int i = 0; i < rating_count; ++i) {
    std::cout << indexes[i] << " ";
  }

  for (int i = 0; i < movie_count; ++i) {
    delete[] movies[i];
  }
  delete[] movies;
  delete[] indexes;

  return 0;
}
