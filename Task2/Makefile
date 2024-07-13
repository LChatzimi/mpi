CC = gcc
CFLAGS = -Wall -O3

EXEC_MPI = task2
EXEC_SERIAL = task2Serial

SRC_MPI = task2.c
SRC_SERIAL = task2Serial.c

HOSTFILE = ../hosts

all: $(EXEC_MPI) $(EXEC_SERIAL)

$(EXEC_MPI): $(SRC_MPI)
	mpicc $(CFLAGS) -o $(EXEC_MPI) $(SRC_MPI)

$(EXEC_SERIAL): $(SRC_SERIAL)
	$(CC) $(CFLAGS) -o $(EXEC_SERIAL) $(SRC_SERIAL)

run_mpi:
	mpirun -hostfile $(HOSTFILE) -np 1 ./$(EXEC_MPI) 32000
	mpirun -hostfile $(HOSTFILE) -np 2 ./$(EXEC_MPI) 32000
	mpirun -hostfile $(HOSTFILE) -np 4 ./$(EXEC_MPI) 32000
	mpirun -hostfile $(HOSTFILE) -np 8 ./$(EXEC_MPI) 32000
	mpirun -hostfile $(HOSTFILE) -np 16 ./$(EXEC_MPI) 32000

run_serial:
	./$(EXEC_SERIAL) 32000

clean:
	rm -f $(EXEC_MPI) $(EXEC_SERIAL)

rebuild: clean all
