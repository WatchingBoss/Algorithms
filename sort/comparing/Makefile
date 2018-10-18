CC = clang
CFLAGS = -std=c99 -O3

OUT = go
OBJ = compare.o

$(OUT): $(OBJ)
	$(CC) $(CFLAGS) -o $(OUT) $(OBJ)

clean:
	$(RM) $(OBJ) $(OUT)
