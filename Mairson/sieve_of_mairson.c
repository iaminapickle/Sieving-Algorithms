#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void crossoff(int *rlink, int *llink, int a);
void printArray(int *arr, int size);
int countArray(int *arr, int size);

int main(void) {
  int n = 10000000;
  int *rlink = calloc(n + 1, sizeof(*rlink));
  int *llink = calloc(n + 2, sizeof(*llink));
  int *del = calloc(n, sizeof(*del));

  for (int i = 1; i <= n; i++) {
    rlink[i] = i + 1;
    llink[i + 1] = i;
  }

  int prime = 2;
  int factor = 2;

  while (prime <= sqrt(n)) {
    int pointer = 0;
    while (prime * factor <= n) {
      int k = prime * factor;
      pointer += 1;
      del[pointer] = k;
      factor = rlink[factor];
    }

    for (int i = 1; i <= pointer; i++) {
      crossoff(rlink, llink, del[i]);
    }

    prime = rlink[prime];
    factor = prime;
  }

  int noPrimes = n / log(n) * (1 + 1.2762 / log(n));
  int *primes = calloc(noPrimes, sizeof(*primes));
  int p = rlink[1];
  int cur = 0;

  while (p < n) {
    primes[cur] = p;
    p = rlink[p];
    cur++;
  }

  printf("%d\n", countArray(primes, noPrimes));
  free(rlink);
  free(llink);
  free(del);
  free(primes);
  return 0;
}

void crossoff(int *rlink, int *llink, int a) {
  rlink[llink[a]] = rlink[a];
  llink[rlink[a]] = llink[a];
}

void printArray(int *arr, int size) {
  for (int i = 0; i < size; i++) {
    if (arr[i] != 0) {
      printf("%d ", arr[i]);
    }
  }
  printf("\n");
}

int countArray(int *arr, int size) {
  int sum = 0;
  for (int i = 0; i < size; i++) {
    if (arr[i] != 0) {
      sum++;
    }
  }
  return sum;
}
