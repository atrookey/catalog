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

int main(int argc, const char * argv[])
{

  // init ncurses
  initscr(); cbreak(); noecho();
  ITEM* items[10];
  for(int i = 0; i < 9; i++) {
    items[i] = new_item("item name", "item description");
  }
  items[9] = NULL;
  MENU *menu = new_menu(items);
  int err = post_menu(menu);
  refresh();

  // input loop
  for(;;) {

  }
  unpost_menu(menu);
  for(int i = 0; i < 9; i++) {
    free_item(items[i]);
  }
  return endwin();
}
