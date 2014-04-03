#VERSION numbers:
#Major.Minor.Release (Date)
#
#Release increments for every pre-compiled binary, which
#aren't being made just yet.
#
#Minor increments when savefiles break. In the future,
#it will be used to check the savefile version.
#
#Major will become 1 when The_Game is "complete".

VER="-DVERSION=\"Version 0.12.1 2014-01-05\""
OBJS=enemy.o file.o formula.o globals.o item.o magic.o main.o

all: $(OBJS)
	gcc $(VER) -O2 -o The_Game obj/enemy.o obj/file.o obj/formula.o obj/globals.o obj/item.o obj/magic.o obj/main.o -w -lncurses -lm

dev: $(OBJS)
	gcc $(VER) -DDEBUG -o The_Game -pg -g obj/enemy.o obj/file.o obj/formula.o obj/globals.o obj/item.o obj/magic.o obj/main.o -Wall -Wextra -Wunused -Wfatal-errors -lncurses -lm

enemy.o:
	gcc $(VER) -o obj/enemy.o -c enemy.c -lncurses -lm

file.o:
	gcc $(VER) -o obj/file.o -c file.c -lncurses -lm

formula.o:
	gcc $(VER) -o obj/formula.o -c formula.c -lncurses -lm

globals.o:
	gcc $(VER) -o obj/globals.o -c globals.c -lncurses -lm

item.o:
	gcc $(VER) -o obj/item.o -c item.c -lncurses -lm

magic.o:
	gcc $(VER) -o obj/magic.o -c magic.c -lncurses -lm

main.o:
	gcc $(VER) -o obj/main.o -c main.c -lncurses -lm

clean:
	rm -rf The_Game gmon.out savefile obj
