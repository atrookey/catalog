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
#include <sqlite3.h>
#include <views.h>
#include <catalog.h>

#define DBNAME "rookey_catalog"

int main(int argc, const char * argv[])
{
  int rc;
  char *zErrMsg = NULL;
  sqlite3 *db;
  WINDOW *my_menu_win;

  // init database 
  rc = sqlite3_open(DBNAME, &db);
  if (rc){
    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return(1);
  }

  // init ncurses
  initscr(); cbreak(); noecho();
  keypad(stdscr, TRUE);
  init_pair(1, COLOR_RED, COLOR_BLACK);

  /* Create the window to be associated with the menu */
  my_menu_win = newwin(10, 40, 4, 4);
  keypad(my_menu_win, TRUE);

  // init book columns
  init_book_columns();

  // open main page
  list_view(db, my_menu_win);

  // cleanup:  unpost_menu(menu);
  // for(int i = 0; i < 9; i++) {
  //   free_item(books[i]);
  // }
  // endwin();
  return endwin();
}
