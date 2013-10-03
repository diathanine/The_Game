VER="-DVERSION=\"Version 0.10.1 2013-09-24\""

all:
	gcc $(VER) -o The_Game main.c -w -lncurses -lm

dev:
	gcc $(VER) -DDEBUG -o The_Game -p -g main.c -Wall -Wextra -Wunused -Wfatal-errors -lncurses -lm

clean:
	rm -f The_Game gmon.out
