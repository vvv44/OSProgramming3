# Complete this rule
vvargas_prog3.o: vvargas_prime.o vvargas_prog3.c
	gcc vvargas_prime.o -c vvargas_prog3.c -o program

# Replace with correct file names
vvargas_prime.o: vvargas_prime.c vvargas_prime.h
	gcc -c vvargas_prime.c

clean:
	rm *.o; rm vvargas_prog3
