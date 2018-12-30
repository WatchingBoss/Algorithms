CXX = clang
CC = clang

CFLAGS = -Wpedantic

OUT = go
OBJ = main.o

$(OUT): $(OBJ)
	$(CC) $(CFLAGS) -o $(OUT) $(OBJ)

clean:
	$(RM) $(OBJ) $(OUT)
