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
  int c;
  ITEM** books;
  ITEM *selected_book;
  MENU *menu;

  books = get_items(db);
  menu = new_menu(books);
  set_menu_format(menu, 24, 1);

  // post the menu
  err = post_menu(menu); // handle this error!

  // input loop
  while((c = getch()) != KEY_F(1)) {
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
        
        // free up memory here!
        unpost_menu(menu);
        if ((err = book_view(db, item_index(selected_book)))) {
          return err;
        }
        err = post_menu(menu); // handle this error!
        break;
      case 'n':
        
        // free up memory here!
        unpost_menu(menu);
        if ((err = new_book_view(db))) {
          return err;
        }
        err = post_menu(menu); // handle this error!
        break;
    }
  }

  // free up memory here!
  unpost_menu(menu);
  return 0;
}

int book_view(sqlite3* db, int index)
{
  int err;
  int c;
  ITEM** info;
  ITEM *selected;
  MENU *menu;

  info = get_item_info(db, index);
  menu = new_menu(info);
  set_menu_format(menu, 24, 1);
  err = post_menu(menu); // handle this error!

  // input loop
  while((c = getch()) != KEY_F(1)) {
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
  
  // free up memory here!
  unpost_menu(menu);
  return 0;
}

int new_book_view(sqlite3* db)
{
  int err;
  int c;
  int toprow;
  FORM  *form;
  FIELD *fields[2*NUMCOLUMNS+1]; // roughly 25
  fields[2*NUMCOLUMNS] = NULL; // roughly index 24
  
  for (int i = 0; i<2*NUMCOLUMNS; i++) {

    /* Initialize the fields */
    fields[i] = new_field(1, 40, i, 0, 0, 0);
    field_opts_off(fields[i], O_ACTIVE); /* This field is a static label */
    set_field_just(fields[i], JUSTIFY_CENTER); /* Center Justification */
    set_field_buffer(fields[i], 0, book_columns[i/2]);

    /* Initialize the fields */
    i++;
    fields[i] = new_field(1, 40, i, 0, 0, 0);

    /* Set field options */
    set_field_back(fields[i], A_UNDERLINE);  /* Print a line for the option  */
    field_opts_off(fields[i], O_AUTOSKIP);   /* Don't go to next field when this */
                                             /* Field is filled up     */
  }

  form = new_form(fields);
  post_form(form);
  refresh();

  // input loop
  while((c = getch()) != KEY_F(1)) {
    switch(c) {
      case KEY_RIGHT:
      case KEY_DOWN:

        /* Go to next field */
        form_driver(form, REQ_NEXT_FIELD);
        form_driver(form, REQ_END_LINE);
        break;
      case KEY_LEFT:
      case KEY_UP:

        /* Go to previous field */
        form_driver(form, REQ_PREV_FIELD);
        form_driver(form, REQ_END_LINE);
        break;
      default:

        /* If this is a normal character, it gets */
        /* Printed          */  
        form_driver(form, c);
        break;
    }
  }
  
  // free up memory here!
  unpost_form(form);
  return 0;
}

int edit_book_view()
{
  return 0;
}

