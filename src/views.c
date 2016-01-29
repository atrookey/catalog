#include <stdio.h>
#include <menu.h>
#include <form.h>
#include <unistd.h>
#include <sqlite3.h>
#include <catalog.h>
#include <views.h>

int list_view(sqlite3 *db, WINDOW *my_menu_win)
{
  int err;
  int i;
  ITEM** books;
  ITEM *selected_book;
  MENU *menu;

  books = get_items(db);
  menu = new_menu(books);

  /* Set main window and sub window */
  set_menu_win(menu, my_menu_win);
  set_menu_sub(menu, derwin(my_menu_win, 6, 38, 3, 1));

  // stuff
  box(my_menu_win, 0, 0);
  // print_in_middle(my_menu_win, 1, 0, 40, "My Menu", COLOR_PAIR(1));
  mvwaddch(my_menu_win, 2, 0, ACS_LTEE);
  mvwhline(my_menu_win, 2, 1, ACS_HLINE, 38);
  mvwaddch(my_menu_win, 2, 39, ACS_RTEE);
  mvprintw(LINES - 2, 0, "q to exit");
  refresh();

  // post the menu
  err = post_menu(menu); // handle this error!
  wrefresh(my_menu_win);

  // input loop
  for (;;) {
    int c = wgetch(my_menu_win);
    switch(c) {
      case KEY_RIGHT:
      case KEY_DOWN:
        menu_driver(menu, REQ_NEXT_ITEM);
        break;
      case KEY_LEFT:
      case KEY_UP:
        menu_driver(menu, REQ_PREV_ITEM);
        break;
      case 10: // ENTER key
        selected_book = current_item(menu);
        unpost_menu(menu);
        if ((err = book_view(db, item_index(selected_book)))) {
          return err;
        }
        err = post_menu(menu); // handle this error!
        break;
      case 'n':
        unpost_menu(menu);
        if ((err = new_book_view())) {
          return err;
        }
        err = post_menu(menu); // handle this error!
        break;
      case 'q':
        return 0;
    }
  }
  return 0;
}

int book_view(sqlite3* db, int index)
{
  int err;
  int i;
  ITEM** info;
  ITEM *selected;
  MENU *menu;

  info = get_item_info(db, index);

  menu = new_menu(info);
  err = post_menu(menu); // handle this error!
  
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
      case 'q':
        return 0;
    }
  }
  return 0;
}

int new_book_view()
{
  return 0;
}

int edit_book_view()
{
  return 0;
}

