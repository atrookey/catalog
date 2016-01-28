all:
	gcc -lsqlite3 -lmenu -lcurses -g src/* -I include -o catalog 
