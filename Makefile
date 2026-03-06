CC = gcc
FLAGS = -lncurses -lm

all:
	$(CC) main.c src/*.c -I./include $(FLAGS) -o proyecto

clean:
	rm -f proyecto