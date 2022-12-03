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

  for (int i = 1; i <= n; i++) {
    rlink[i] = i + 1;
    llink[i + 1] = i;
  }

  unsigned long long prime = 2;
  unsigned long long factor = 2;

  do {
    factor = rlink[factor];
  } while (prime * factor <= n);
  factor = llink[factor];

  while (prime <= sqrt(n)) {
    while (factor != 0) {
      int k = prime * factor;
      factor = llink[factor];
      crossoff(rlink, llink, k);
    }

    prime = rlink[prime];
    factor = 2;
    do {
      factor = rlink[factor];
    } while (prime * factor <= n);
    factor = llink[factor];
  }

  int noPrimes = n / log(n) * (1 + 1.2762 / log(n));
  int *primes = calloc(noPrimes, sizeof(*primes));
  rlink[1] = 2;
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
  free(primes);
  return 0;
}

void crossoff(int *rlink, int *llink, int a) {
  llink[rlink[a]] = llink[a];
  rlink[llink[a]] = rlink[a];
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
