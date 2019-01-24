CC = gcc
CFLAGS = -Wpedantic -O3

OUT = go
OBJ = merge.o

$(OUT): $(OBJ)
	$(CC) $(CFLAGS) -o $(OUT) $(OBJ)

clean:
	$(RM) $(OBJ) $(OUT)
