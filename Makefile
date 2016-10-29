all: objs
	gcc -Itimer_setup.h *.o -o obj -lrt
	rm -rf *.o
objs:
	gcc -c timer_setup.c -lrt
	gcc -c example_timer.c -lrt
clean:
	rm -rf *.o obj