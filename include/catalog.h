//
//  catalog.h
//  Rookey Catalog
//
//  Created by Alexander Rookey on 1/27/16.
//  Copyright © 2016 Alexander Rookey. All rights reserved.
//

// Paths
#define DBNAME "/Users/alexander/Development/rookey_catalog/rookey_catalog"

// Sql
#define SELECTALL "SELECT * FROM books;"
#define COUNTALL "SELECT COUNT(*) FROM books;"
#define SELECTALLWHEREID "SELECT * FROM books WHERE ID="
#define INSERTVALUES "INSERT INTO books " \
    "(call_number, author, title, edition, publication_location, publisher, " \
    "publication_date, series_title, notes, isbn, subject)" \
    "VALUES"

// Columns
#define NUMCOLUMNS 12
#define ID 0
#define CALLNUMBER 1
#define AUTHOR 2
#define TITLE 3
#define EDITION 4
#define PUBLICATIONLOCATION 5
#define PUBLISHER 6
#define PUBLICATIONDATE 7
#define SERIESTITLE 8
#define NOTES 9
#define ISBN 10
#define SUBJECT 11

// Other
#define NULLVALUE "NULL"

static char** index_id_map;
static char* book_columns[NUMCOLUMNS];
static sqlite3 *db;

// I wish I could get rid of this struct
struct items_builder {
  int count;
  ITEM** items;
};

int init_catalog(void);
void init_book_columns(void);

// hooks
void init_main_menu(MENU*);
void term_main_menu(MENU*);

void init_book_menu(MENU*);
void term_book_menu(MENU*);

void init_new_book_form(FORM*);
void term_new_book_form(FORM*);

void init_edit_book_form(FORM*);
void term_edit_book_form(FORM*);

// void delete_item(void); // idk yet

// // __ Main Menu __
// // Enter main menu
// ITEM** get_items(MENU*); // set_menu_init

// // Exit main menu
// ITEM* get_current_item(MENU*); // set_menu_term
// int set_current_id(ITEM*); // global current_id variable?

// // __ Book Menu __
// // Enter book menu
// ITEM** get_item_info(MENU*);  // set_menu_init

// // Exit book menu
// void 

// // __ New Book Form __
// // Enter new book form

// // Exit new book form
// void add_item();  // set_form_term

// // __ Edit Book Form __
// // Enter edit book form

// // Exit edit book form
// void edit_item(void); // set_form_term