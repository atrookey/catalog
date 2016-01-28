//
//  main.c
//  Rookey Catalog
//
//  Created by Alexander Rookey on 1/27/16.
//  Copyright © 2016 Alexander Rookey. All rights reserved.
//

#include <stdio.h>
#include <menu.h>
#include <form.h>
#include <unistd.h>
#include <catalog.h>
#include <sqlite3.h>

#define DBNAME "rookey_catalog"

int main(int argc, const char * argv[])
{
  int rc;
  char *zErrMsg = NULL;
  sqlite3 *db;

  // init database 
  rc = sqlite3_open(DBNAME, &db);
  if (rc){
    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return(1);
  }
  // rc = sqlite3_exec(db, );
  // if (rc!=SQLITE_OK){
  //   fprintf(stderr, "SQL error: %s\n", zErrMsg);
  //   sqlite3_free(zErrMsg);
  // }
  
  // init ncurses
  initscr(); cbreak(); noecho();
  keypad(stdscr, TRUE);
  ITEM** items;
  for(int i = 0; i < 9; i++) {
    items = getItems();
  }
  MENU *menu = new_menu(items);
  int err = post_menu(menu);
  refresh();

  // input loop
  for (;;) {
    int c = getch();
    switch(c) {
      case KEY_RIGHT:
      case KEY_DOWN:
        menu_driver(menu, REQ_NEXT_ITEM);
        break;
      case KEY_LEFT:
      case KEY_UP:
        menu_driver(menu, REQ_PREV_ITEM);
        break;
    }
  }

  unpost_menu(menu);
  for(int i = 0; i < 9; i++) {
    free_item(items[i]);
  }
  return endwin();
}
