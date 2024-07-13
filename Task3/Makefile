CC = mpicc
CFLAGS = -Wall -O3 -fopenmp

EXEC = task3

SRC = task3.c

HOSTFILE = hosts

$(EXEC): $(SRC)
	$(CC) $(CFLAGS) -o $(EXEC) $(SRC)

run:
	OMP_NUM_THREADS=4 mpirun -hostfile $(HOSTFILE) -np 1 ./$(EXEC) 1000000000
	OMP_NUM_THREADS=4 mpirun -hostfile $(HOSTFILE) -np 2 ./$(EXEC) 1000000000
	OMP_NUM_THREADS=4 mpirun -hostfile $(HOSTFILE) -np 4 ./$(EXEC) 1000000000
	OMP_NUM_THREADS=4 mpirun -hostfile $(HOSTFILE) -np 8 ./$(EXEC) 1000000000
	OMP_NUM_THREADS=4 mpirun -hostfile $(HOSTFILE) -np 16 ./$(EXEC) 1000000000

clean:
	rm -f $(EXEC)

rebuild: clean $(EXEC)
