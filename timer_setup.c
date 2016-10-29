#include "timer_setup.h"

int count;

void timer_init()
{
	count = -1;
}

static void handler(int sig, siginfo_t *si, void *uc)
{
	timer_info_t* timer_info;
	timer_info = si->si_value.sival_ptr;
	//if(timer_info->timer_enabled)
	timer_info->timerspecific_handler();
}


void setup_sigaction(struct sigaction* sa, sigset_t* mask)
{
	sigemptyset(mask);
	if (sigprocmask(SIG_UNBLOCK, mask, NULL) == -1)
		errExit("sigprocmask");

	sa->sa_flags = SA_SIGINFO;
	sa->sa_sigaction = handler;
	sigemptyset(&(sa->sa_mask));
	if (sigaction(SIG, sa, NULL) == -1)
		errExit("sigaction");
}

void timercreate(timer_t* timerid, struct sigevent* sev, void (* handler)(int, siginfo_t*, void*), timer_info_t* timer_info)
{

	sev->sigev_notify = SIGEV_SIGNAL;
	sev->sigev_signo = SIG;
	sev->sigev_value.sival_ptr = timer_info;      //Timer address passed to the handler     
	if (timer_create(CLOCKID, sev, timerid) == -1)
	 errExit("timer_create");
	timer_info->timerID = timerid;
}

void timer_start(struct itimerspec* its, timer_t* timerid, float freq, int mode)
{

	//Start the timer 
	if(freq<=1)
	{
		its->it_value.tv_sec = 1/freq;
		its->it_value.tv_nsec = 0;
	}
	else
	{
		its->it_value.tv_sec = 0;
		its->it_value.tv_nsec = 1000000000/freq;
	}
	switch(mode) {
		case 0:				//One shot mode
			its->it_interval.tv_sec = 0;
			its->it_interval.tv_nsec = 0;
			break;
		case 1:				//Periodic mode
			its->it_interval.tv_sec = its->it_value.tv_sec;
			its->it_interval.tv_nsec = its->it_value.tv_nsec;
		    break;


		default:
			errExit("Invalid mode\n");
	}
	if (timer_settime(*timerid, 0, its, NULL) == -1)   //Start timer
	  errExit("timer_settime");
} 

void timer_info_init(timer_info_t* timer_info, void (* timer_handler)())
{
	timer_info->timerspecific_handler = timer_handler;
	//timer_info->timer_enabled = 1;
}

int start_timer(void (*timerspecific_handler)(void), float freq, int mode)
{
	count++;
	timer_t timerid;
	struct sigevent sev;
	struct itimerspec its;
	sigset_t mask;
	struct sigaction sa;
	timer_info_t* timer_info;
	timer_info = (timer_info_t*)malloc(sizeof(timer_info_t));

	timer_info_init(timer_info,timerspecific_handler);
	setup_sigaction(&sa, &mask);                           //Setup sigaction for the timer
	timercreate(&timerid, &sev, &handler, timer_info);     //Create the timer
	timer_start(&its, &timerid, freq, mode);                           //Start the timer

	return count;	
}