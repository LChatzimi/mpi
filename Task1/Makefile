CC = mpicc
CFLAGS = -Wall -O3

EXEC = task1

SRC = task1.c

HOSTFILE = ../hosts

$(EXEC): $(SRC)
	$(CC) $(CFLAGS) -o $(EXEC) $(SRC)

run:
	mpirun -hostfile $(HOSTFILE) -np 1 ./$(EXEC) 100000000
	mpirun -hostfile $(HOSTFILE) -np 2 ./$(EXEC) 100000000
	mpirun -hostfile $(HOSTFILE) -np 4 ./$(EXEC) 100000000
	mpirun -hostfile $(HOSTFILE) -np 8 ./$(EXEC) 100000000
	mpirun -hostfile $(HOSTFILE) -np 16 ./$(EXEC) 100000000
clean:
	rm -f $(EXEC)

rebuild: clean $(EXEC)



