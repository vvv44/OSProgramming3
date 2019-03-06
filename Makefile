all: vvargas_prime.o vvargas_prog3.o
	gcc vvargas_prime.o vvargas_prog3.o -o program

# Complete this rule
vvargas_prog3.o: vvargas_prime.o vvargas_prog3.c
	gcc -c vvargas_prog3.c

# Replace with correct file names
vvargas_prime.o: vvargas_prime.c vvargas_prime.h
	gcc -c vvargas_prime.c

clean:
	rm *.o; rm vvargas_prog3
