#include "timer_setup.h"

void timer1_func(void)
{
  printf("Timer1_handler\n");
}                                                               

void timer2_func(void)
{
  printf("AAAAAAAAAAAAAAAAAAAAa\n");
}                   

void timer3_func(void)
{
  printf("Timer3_handler\n");
}                   

int main()
{
  int id;
  timer_init();
  start_timer(timer1_func, 1, 1);
  start_timer(timer2_func,1,0);
  start_timer(timer3_func, 1, 1);
  while(1);
}