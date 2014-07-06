DEFS=""
OBJS=enemy.o file.o formula.o globals.o item.o magic.o main.o

all: $(OBJS)
	gcc $(DEFS) -O2 -o The_Game obj/enemy.o obj/file.o obj/formula.o obj/globals.o obj/item.o obj/magic.o obj/main.o -w -lncurses -lm

dev: $(OBJS)
	gcc $(DEFS) -DDEBUG -o The_Game -pg -g obj/enemy.o obj/file.o obj/formula.o obj/globals.o obj/item.o obj/magic.o obj/main.o -Wall -Wextra -Wunused -Wfatal-errors -lncurses -lm

enemy.o:
	gcc $(DEFS) -o obj/enemy.o -c enemy.c -lncurses -lm

file.o:
	gcc $(DEFS) -o obj/file.o -c file.c -lncurses -lm

formula.o:
	gcc $(DEFS) -o obj/formula.o -c formula.c -lncurses -lm

globals.o:
	gcc $(DEFS) -o obj/globals.o -c globals.c -lncurses -lm

item.o:
	gcc $(DEFS) -o obj/item.o -c item.c -lncurses -lm

magic.o:
	gcc $(DEFS) -o obj/magic.o -c magic.c -lncurses -lm

main.o:
	gcc $(DEFS) -o obj/main.o -c main.c -lncurses -lm

clean:
	rm -rf The_Game gmon.out savefile obj
