SRC = $(wildcard *.c)
OBJ = ${SRC:.c=.o}
OUT = echo

all: $(OUT)

$(OUT): $(OBJ)
	$(CC) $^ -o $@

%.o: %.c
	$(CC) -c $< -o $@

clean:
	rm -f $(OUT) $(OBJ)
