CC = gcc
CFLAGS = -g -Wall -Wpedantic -std=c11

OBJ = timsort.o
OUT = go

$(OUT): $(OBJ)
	$(CC) $(CFLAGS) -o $(OUT) $(OBJ)

clean:
	$(RM) $(OBJ) $(OUT)
