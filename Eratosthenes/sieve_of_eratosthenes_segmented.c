#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void printArray(int *arr, int size);
int find_start(int segStart, int p);
void reset_segment(bool *seg, int segSize);
void sieve_prime(int segStart, int segEnd, int p, bool *seg);
void update_primes(int segStart, int segEnd, bool *seg, int *primes,
                   int *curIndex, long end);
int countArray(int *arr, int size);
void sieve(int start, long end, int *arr, int *endIndex);

int main(void) {
  long end = 10000000;
  int noPrimes = floor((end / log(end)) * (1 + 1.2762 / log(end)));
  int *primes = (int *)calloc(noPrimes, sizeof(*primes));
  int endIndex = 0;
  int delta = floor(sqrt(end));
  int segSize = delta / 2 + 1;
  bool *seg = (bool *)calloc(segSize, sizeof(*seg));
  primes[0] = 2;

  sieve(3, delta, primes, &endIndex);
  int curIndex = endIndex + 1;

  for (int i = delta + 1; i < end; i += delta) {
    for (int j = 1; j <= endIndex; j++) {
      sieve_prime(i, i + delta, primes[j], seg);
    }
    update_primes(i, i + delta, seg, primes, &curIndex, end);
    reset_segment(seg, segSize);
  }

  // printArray(primes, noPrimes);
  printf("%d\n", countArray(primes, noPrimes));
  free(primes);
  free(seg);
}

void sieve(int start, long end, int *arr, int *endIndex) {
  for (int i = 0; 2 * i + 3 < end; i++) {
    int val = 2 * i + 3;
    if (arr[i + 1] == 0) {
      for (int j = val * val; j <= end; j += 2 * val) {
        arr[(j - 3) / 2 + 1] = 1;
      }
    }
  }

  int cur = 1;
  for (int i = 0; 2 * i + 3 <= end; i++) {
    if (arr[i + 1] == 0) {
      arr[cur] = 2 * i + 3;
      (*endIndex)++;
      cur++;
    } else {
      arr[i + 1] = 0;
    }
  }
  return;
}

void sieve_prime(int segStart, int segEnd, int p, bool *seg) {
  int segStart_odd = (segStart % 2) ? segStart : segStart + 1;
  int start = find_start(segStart_odd, p);

  if (start > segEnd) {
    return;
  }
  for (int i = start; i < segEnd; i += 2 * p) {
    int index = (i - segStart_odd) / 2;
    if (seg[index] == 0) {
      seg[index] = 1;
    }
  }
  return;
}

void update_primes(int segStart, int segEnd, bool *seg, int *primes,
                   int *curIndex, long end) {
  int segStart_odd = (segStart % 2) ? segStart : segStart + 1;
  for (int i = segStart_odd; i < segEnd; i += 2) {
    int index = (i - segStart_odd) / 2;
    if (i <= end && seg[index] == 0) {
      primes[*curIndex] = i;
      (*curIndex)++;
    }
  }
}

int find_start(int segStart, int p) {
  if (segStart % p == 0) {
    return segStart;
  }
  int start = segStart + p - (segStart % p);
  return (start % 2) ? start : start + p;
}

void reset_segment(bool *seg, int segSize) {
  for (int i = 0; i < segSize; i++) {
    seg[i] = 0;
  }
}

void printArray(int *arr, int size) {
  for (int i = 0; i < size; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

int countArray(int *arr, int size) {
  int count = 0;
  for (int i = 0; i < size; i++) {
    if (arr[i] != 0) {
      count++;
    }
  }
  return count;
}
