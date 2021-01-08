#include <stdio.h>
#include <stdbool.h>
#include "linked-list.h"



typedef int kuku;
typedef int* kuku2;

struct numbers
{
  int num1;
  int num2;
  double num3;
};
typedef struct numbers numbers_t;

typedef double(*func)(int, double);
typedef void (*n_func)(struct numbers*, int);

void add_number(struct numbers* head_num, int x){
  head_num->num1 = x;
}
bool moshe(n_func chaim){
  struct numbers my_num;
  my_num.num1=1;
  my_num.num2=2;
  my_num.num3=3.3;
  int a = 5;
  chaim(&my_num, a);
  return true;
}
double foo(int x, double y)
{
  return y-x;
}

double bar(func user_func)
{
  double ret_val = user_func(5, 5.5);
  return ret_val;
}

struct number
{
  int num1;
};

int clone_num(void *in_elem, void **out_elem){
  struct  number *x;
  in_elem = x;
}
/* User function, Destroy “element”. always succeed */
typedef void(*element_destroy_t)(void *element);

int main() {
    printf("Hello, World!\n");
    double result = bar(foo);
    printf("%f\n", result);
    bool b = moshe(add_number);
  printf("%d\n", b);
    return 0;
}