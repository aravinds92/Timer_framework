all: objs
	gcc *.o -o obj -lrt
	rm -rf *.o
	./obj
objs:
	gcc -c timer_setup.c -lrt
	gcc -c example_timer.c -lrt
clean:
	rm -rf *.o obj