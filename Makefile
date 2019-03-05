# Complete this rule
student_prog3: student_prime.o student_prog3.c
	gcc ???

# Replace with correct file names
student_prime.o: student_prime.c student_prime.h
	gcc -c student_prime.c

clean:
	rm *.o; rm student_prog3
