CC = gcc
CFLAGS = -Wall -lm -O3
EXE = main
SRC = main.c functions.c
 
$(EXE):$(SRC)
	$(CC) $(CFLAGS) -o $(EXE) $(SRC)
 
clean:
	rm -f $(EXE)
