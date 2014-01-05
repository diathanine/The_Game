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

VER="-DVERSION=\"Version 0.11.1 2014-01-05\""

all:
	gcc $(VER) -o The_Game main.c -w -lncurses -lm

dev:
	gcc $(VER) -DDEBUG -o The_Game -p -g main.c -Wall -Wextra -Wunused -Wfatal-errors -lncurses -lm

clean:
	rm -f The_Game gmon.out savefile
