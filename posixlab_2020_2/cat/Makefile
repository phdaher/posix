SRC = $(wildcard *.c)
OBJ = ${SRC:.c=.o}
OUT = cat

all: $(OUT)

$(OUT): $(OBJ)
	$(CC) $^ -o $@

%.o: %.c
	$(CC) -c $< -o $@

clean:
	rm -f $(OUT) $(OBJ)
