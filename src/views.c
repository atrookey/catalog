#include <stdio.h>
#include <menu.h>
#include <form.h>
#include <unistd.h>
#include <sqlite3.h>
#include <catalog.h>
#include <views.h>

int list_view(sqlite3 *db)
{
  int err;
  int i;
  ITEM** books;
  ITEM *selected_book;
  MENU *menu;

  books = get_items(db);
  menu = new_menu(books);
  set_menu_format(menu, 24, 1);


  // post the menu
  err = post_menu(menu); // handle this error!

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
  set_menu_format(menu, 24, 1);
  err = post_menu(menu); // handle this error!

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
        unpost_menu(menu);
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

