#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void printArray(bool *arr, int size);
int countArray(bool *arr, int size);

int main(void) {
  int start = 3;
  int end = 10000000;
  int size = end - start;
  bool *arr = (bool *)calloc(size + 1, sizeof(*arr));

  for (int i = 0; i < sqrt(end); i++) {
    if (arr[i] == 0) {
      for (int j = (i+2) * (i+2); j < end; j += i + 2) {
        arr[j - 2] = 1;
      }
    }
  }
  //printArray(arr, size);
  printf("%d\n", countArray(arr, size));
  free(arr);
}

void printArray(bool *arr, int size) {
  for (int i = 0; i < size; i++) {
    if (!arr[i]) {
      printf("%d ", !arr[i] * (i + 2));
    }
  }
  printf("\n");
}

int countArray(bool *arr, int size) {
  int sum = 0;
  for (int i = 0; i < size; i++) {
    if (!arr[i]) {
      sum++;
    }
  }
  return sum;
}
