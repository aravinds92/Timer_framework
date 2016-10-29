#ifndef TIMER_SETUP_H
#define TIMER_SETUP_H
#endif

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>

#define CLOCKID CLOCK_REALTIME
#define SIG SIGRTMIN
#define errExit(msg)    do { perror(msg); exit(EXIT_FAILURE); \
                       } while (0)

typedef struct timer_info_s				//struct to hold timer specific data
{
  timer_t* timerID;
  int timer_enabled;  
  void (*timerspecific_handler)();
}timer_info_t;


void timer_init(void);
static void handler(int, siginfo_t*, void*);
void setup_sigaction(struct sigaction*, sigset_t*);
void timercreate(timer_t*, struct sigevent*, void (*handler)(int, siginfo_t*, void*), timer_info_t*);
void timer_start(struct itimerspec*, timer_t*, float, int);
void timer_info_init(timer_info_t*, void (*timer_handler)());
int start_timer(void (*timerspecific_handler)(void), float, int);