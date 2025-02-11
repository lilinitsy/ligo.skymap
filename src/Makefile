CC = gcc
CFLAGS = -O3 -Wall -Wextra -march=native -std=c11
LDFLAGS = -lm 
OBJ = cubic_interp.o cubic_interp_optimizations_tests.o
DEPS = cubic_interp.h branch_prediction.h vmath.h

all: cubic_interp_optimizations_tests

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

cubic_interp_optimizations_tests: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f *.o cubic_interp_optimizations_tests

