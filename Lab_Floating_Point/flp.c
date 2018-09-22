//  Ubuntu 32-bit
//  gcc version 5.4.0 20160609
//  gcc flp.c -lm -o flp (link the code against the math lib)
#include <stdio.h>
#include <stddef.h>  //  size_t
#include <math.h>  //  log10(), isfinite(), trunc()
#include <limits.h>  //  UINT_MAX
#include <float.h>  //  FLT_DIG
#include <stdint.h>  //  uintmax_t
#include <assert.h>  //  assert()
#include <stdbool.h>  //  true, false
#include <string.h>  //  memcmp()
#include <stdlib.h>  //  malloc(), free()

void func1(void) {  //  Do not use floating-point variables as loop counters
    float x;

    for (x = 5.0f; x >= 1.0f; x -= 0.4f) {
        printf("%f\n", x);
    }
    printf("\n\n");

    x = 5.0f;
    float y = x;
    for (size_t count = 1; count <= 11; ++count) {  // Loop iterates exactly 11 times
        printf("%f\n", y);
        y = x - count * 0.4f;
    }
}

double safe_log10(double arg) {
    //  log() Domain: x >= 0
    if (arg <= 0) {
        fprintf(stderr, "log10() requires a nonnegative argument\n");
        /* Handle domain / pole error */
    }
    return log10(arg);
}

void func2(void) {  //  Prevent or detect domain and range errors in math functions
	//  INF -> infinite
	//  NAN -> Not a number
	//  IND -> indefinite

    printf("log10(0.0) = %lf\n", log10(0.0));
    printf("log10(-10.0) = %lf\n\n", log10(-10.0));

    safe_log10(0.0);
    safe_log10(-10.0);
}

void func3(void) {  //  Ensure that floating-point conversions are within range of the new type
    float v = -1.0f;
    unsigned int i_a = (int)v;

    printf("%u\n\n", i_a);


    float d;
    if (!isfinite(v)) {
        printf("isfinite(v) failed.\n");
        return;
    }
    d = trunc(v);
    if (!((d>=0.0) && (d<=(float)UINT_MAX))) {
        printf("((d>=0.0) && (d<=(float)UINT_MAX)) failed.\n");
        return;
    }
    i_a = (unsigned int)d;
    printf("%u\n", i_a);
}

/* Returns the number of set bits */
size_t popcount(uintmax_t num) {
  size_t precision = 0;
  while (num != 0) {
    if (num % 2 == 1) {
      precision++;
    }
    num >>= 1;
  }
  return precision;
}
#define PRECISION(umax_value) popcount(umax_value)

void func4(void) {  //  Preserve precision when converting integral values to floating-point type
    long int big = 1234567891;
    float approx = big;

    printf("%d\n", FLT_DIG);  // # of decimal digits of precision

    printf("big = %ld\n", big);
    printf("approx = %f\n", approx);
    printf("big - (long int)approx = %ld\n\n", (big - (long int)approx));

    assert(PRECISION(LONG_MAX) <= DBL_MANT_DIG * log2(FLT_RADIX));
    double dapprox = big;
    printf("big = %ld\n", big);
    printf("dapprox = %f\n", dapprox);
    printf("big - (long int)dapprox = %ld\n", (big - (long int)dapprox));
}

struct S {
    long l;
    float f;
};

bool are_equal1(const struct S *s1, const struct S *s2) {
    if (!s1 && !s2)
        return true;
    else if (!s1 || !s2)
        return false;
    return 0 == memcmp(s1, s2, sizeof(struct S));  //  memcmp() is used to compare two structures for equality
}

bool are_equal2(const struct S *s1, const struct S *s2) {
    if (!s1 && !s2)
        return true;
    else if (!s1 || !s2)
        return false;
    return s1->l == s2->l && s1->f == s2->f;  //  the structure members are compared individually
}

void func5(void) {  //  Do not use object representations to compare floating-point values
    struct S *s1, *s2;
    s1 = malloc(sizeof(struct S));
    s2 = malloc(sizeof(struct S));
    s1->l = 1;
    s1->f = -0.0;
    s2->l = 1;
    s2->f = 0.0;

    if (are_equal1(s1, s2)) {
        printf("equal\n");
    }
    else {
        printf("not equal\n\n");
    }


    if (are_equal2(s1, s2)) {
        printf("equal\n");
    }
    else {
        printf("not equal\n\n");
    }
    free(s1);
    free(s2);
}

int main() {
    func1();
    printf("\n----------\n\n");
    func2();
    printf("\n----------\n\n");
    func3();
    printf("\n----------\n\n");
    func4();
    printf("\n----------\n\n");
    func5();

    return 0;
}
