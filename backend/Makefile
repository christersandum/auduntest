CC = gcc
CFLAGS = -Wall -Wextra -O2 -Isrc
SRCS = src/main.c src/routes.c src/mongoose.c
OUT = server

all: $(OUT)

$(OUT): $(SRCS)
	$(CC) $(CFLAGS) -o $(OUT) $(SRCS) -lpthread

clean:
	rm -f $(OUT)

run: $(OUT)
	./$(OUT)

.PHONY: all clean run
