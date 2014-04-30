pid:pid.o
	cc -o pid pid.o
pid.o:pid.c
	cc -c pid.c
clean:
	rm pid.o
