CC = g++
CFLAGS = -Wall -std=c++11

all: tsp_solver

tsp_solver: tsp_solver.o
	$(CC) $(CFLAGS) tsp_solver.o -o tsp_solver

tsp_solver.o: tsp_solver.cpp
	$(CC) $(CFLAGS) -c tsp_solver.cpp

clean:
	rm -f *.o tsp_solver
