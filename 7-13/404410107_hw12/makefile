all: pi.c
	gcc ./pi.c -o pi -pthread
run:
	time ./pi 10000000 2
	time ./pi 10000000 1
auto: all run
