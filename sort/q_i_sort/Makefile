CC = gcc
CFLAGS = -Wpedantic -Wall -O3

OUT = go
OBJ = sort.o

$(OUT): $(OBJ)
	$(CC) $(CFLAGS) -o $(OUT) $(OBJ)

clean:
	$(RM) $(OBJ) $(OUT)
