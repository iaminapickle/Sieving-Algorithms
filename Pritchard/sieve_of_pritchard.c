#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void crossoff(int *rlink, int *llink, int a);
void printArray(int *arr, int size);
void printLinkArray(int *arr, int n);
int countLinkArray(int *arr, int n);
int countArray(int *arr, int size);
void add_to_wheel(int *rlink, int *llink, int val, int *last_wheel_val);
void remove_from_wheel(int *rlink, int *llink, int n);
void extend(int *rlink, int *llink, int *primes, int *wheel_length,
            int *last_wheel_val, int n);
void cleanup(int *rlink, int *llink, int *primes, int wheel_length, int n);
void add_prime(int *primes, int p);
void remove_prime_from_wheel(int *rlink, int *llink, int *primes, int p,
                             int wheel_length, int n);

int main(void) {
  int n = 10000000;
  int *rlink = calloc(n + 1, sizeof(*rlink));
  int *llink = calloc(n + 2, sizeof(*llink));
  int last_wheel_val = 5;
  int wheel_length = 6;
  int noPrimes =
      ceil(sqrt(n)) / log(ceil(sqrt(n))) * (1 + 1.2762 / log(ceil(sqrt(n))));
  int *primes = calloc(noPrimes, sizeof(*primes));

  rlink[0] = 1;
  rlink[1] = 5;
  llink[5] = 1;
  primes[0] = 2;
  primes[1] = 3;

  while (wheel_length < n) {
    extend(rlink, llink, primes, &wheel_length, &last_wheel_val, n);
  }
  cleanup(rlink, llink, primes, wheel_length, n);

  // printLinkArray(rlink, n);
  // printArray(primes, noPrimes);
  printf("%d\n", countLinkArray(rlink, n) + countArray(primes, noPrimes));
  free(rlink);
  free(llink);
  free(primes);
  return 0;
}

void extend(int *rlink, int *llink, int *primes, int *wheel_length,
            int *last_wheel_val, int n) {
  int p = rlink[1];
  add_prime(primes, p);

  int length = *wheel_length;
  *wheel_length *= p;

  int cur = 0;
  while (1) {
    cur = rlink[cur];
    if (cur + length > *wheel_length || cur + length > n) {
      break;
    }
    int val = cur + length;
    add_to_wheel(rlink, llink, val, last_wheel_val);
  }

  remove_prime_from_wheel(rlink, llink, primes, p, *wheel_length, n);
}

void cleanup(int *rlink, int *llink, int *primes, int wheel_length, int n) {
  while (1) {
    int p = rlink[1];
    if (p * p > n) {
      break;
    }
    add_prime(primes, p);
    remove_prime_from_wheel(rlink, llink, primes, p, wheel_length, n);
  }
}

void remove_prime_from_wheel(int *rlink, int *llink, int *primes, int p,
                             int wheel_length, int n) {
  int index = 0;
  int cur = 0;

  while (cur * p <= wheel_length && cur * p <= n) {
    cur = rlink[cur];
  }

  while (cur != 0) {
    cur = llink[cur];
    if (cur == 0) {
      break;
    }
    int val = cur * p;
    if (rlink[val] != 0) {
      remove_from_wheel(rlink, llink, val);
    }
  }
}

void add_prime(int *primes, int p) {
  int i = 0;
  while (1) {
    if (primes[i] == 0) {
      primes[i] = p;
      break;
    }
    i++;
  }
}

void add_to_wheel(int *rlink, int *llink, int val, int *last_wheel_val) {
  rlink[*last_wheel_val] = val;
  rlink[val] = -1;
  llink[val] = *last_wheel_val;

  *last_wheel_val = val;
}

void remove_from_wheel(int *rlink, int *llink, int n) {
  if (rlink[n] == -1) {
    rlink[llink[n]] = -1;
  } else {
    rlink[llink[n]] = rlink[n];
    llink[rlink[n]] = llink[n];
  }
  rlink[n] = 0;
  llink[n] = 0;
}

void printLinkArray(int *arr, int n) {
  int cur = arr[1];
  while (1) {
    printf("%d ", cur);
    cur = arr[cur];
    if (cur == -1 || cur > n) {
      break;
    }
  }
  printf("\n");
}

int countLinkArray(int *arr, int n) {
  int cur = arr[1];
  int sum = 1;
  while (1) {
    cur = arr[cur];
    if (cur == -1 || cur > n) {
      break;
    }
    sum++;
  }
  return sum;
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
