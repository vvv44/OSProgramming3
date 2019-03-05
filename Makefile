# Complete this rule
vvargas_prog3: vvargas_prime.o vvargas_prog3.c
	gcc ???

# Replace with correct file names
vvargas_prime.o: vvargas_prime.c vvargas_prime.h
	gcc -c vvargas_prime.c

clean:
	rm *.o; rm vvargas_prog3
