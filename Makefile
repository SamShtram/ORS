CC=gcc
CFLAGS=-Wall -pthread -Iinclude

SRC=src/main.c \
    src/queue.c \
    src/algorithms.c \
    src/scheduler.c \
    src/or_thread.c \
    src/utils.c

OUT=orsim

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)
