all:
	gcc -lsqlite3 -lform -lmenu -lcurses -g src/* -I include -o rcat
