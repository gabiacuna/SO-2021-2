#include <stdio.h>
#include “sthread.h”
#include <math.h>

static sthread_t l;
static sthread_t f;

static void lucas(int n);
static void fib(int n);
static void igualdad(int n);

int main (int argc, char**argv) {

    int n;
    scanf("%d", &n)

    sthread_create(&l, &lucas, n);
    sthread_create(&f, &fib, n);

    int res = sthread_join(l);
    res += sthread_join(f)*sqrt(5);
    res /= 2;

    return 0;
}

void lucas(int n){
    int x;
    if(n==0){
        x = 2;
    } else if (n == 1)
    {
        x = 1;
    } else
    {
        sthread_t n1, n2;
        sthread_create(&n1, &lucas, n-1);
        sthread_create(&n2, &lucas, n-2);
        x = sthread_join(n1) + sthread_join(n2);
    }

    sthread_exit(x);   
}

void fib(int n){
    int x;
    if(n==0){
        x = 0;
    } else if (n == 1)
    {
        x = 1;
    } else
    {
        sthread_t n1, n2;
        sthread_create(&n1, &fib, n-1);
        sthread_create(&n2, &fib, n-2);
        x = sthread_join(n1) + sthread_join(n2);
    }

    sthread_exit(x);   
}

void igualdad(int n){
    int x;
    sthread_t n1, n2;
    sthread_create(&n1, &lucas, n-1);
    sthread_create(&n2, &lucas, n+1);
    x = sthread_join(n1) + sthread_join(n2);
    x = x/5;

    sthread_exit(x);
}