CC = mpicc
CFLAGS = -Wall -O3
 
EXEC = task1
 
SRC = task1.c
 
$(EXEC): $(SRC)
	$(CC) $(CFLAGS) -o $(EXEC) $(SRC)
 
run:
	mpirun  -np 1 ./$(EXEC) 100000000
	mpirun  -np 2 ./$(EXEC) 100000000
	mpirun  -np 4 ./$(EXEC) 100000000
 
clean:
	rm -f $(EXEC)
 
rebuild: clean $(EXEC)