#include "timer_setup.h"

long int count = 0;

void timer1_func(void)
{
  count++;
}                                                               

void timer2_func(void)
{
  printf("%ld\n",count);
  count = 0;
}                   
                  

int main()
{
  start_timer(timer1_func, 100000, 1);		
  start_timer(timer2_func, 1, 1);
  while(1);
}