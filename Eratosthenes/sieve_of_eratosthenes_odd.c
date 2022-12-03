#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int countOdd(int start, int end);
void printArray(bool *arr, int size);
int countArray(bool *arr, int size);

int main(void) {
  int start = 3;
  long end = 10000000;
  int odd = countOdd(start, end);
  bool *arr = (bool *)calloc(odd + 1, sizeof(*arr));

  for (int i = 1; 2 * (i - 1) + 3 < sqrt(end); i++) {
    int val = 2 * (i - 1) + 3;
    if (arr[i] == 0) {
      for (int j = (val) * (val) ; j < end; j += 2 * val) {
        arr[(j - 3) / 2 + 1] = 1;
      }
    }
  }
  printf("%d\n", countArray(arr, odd));
  free(arr);
}

int countOdd(int start, int end) {
  if (start % 2 || end % 2) {
    return (end - start) / 2 + 1;
  } else {
    return (end - start) / 2;
  }
}

void printArray(bool *arr, int size) {
  printf("2 ");
  for (int i = 1; i < size; i++) {
    if (!arr[i]) {
      printf("%d ", !arr[i] * (2 * (i - 1) + 3));
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
