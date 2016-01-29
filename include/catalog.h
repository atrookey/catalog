//
//  catalog.h
//  Rookey Catalog
//
//  Created by Alexander Rookey on 1/27/16.
//  Copyright © 2016 Alexander Rookey. All rights reserved.
//

// Queries
#define SELECTALL "SELECT * FROM books;"
#define COUNTALL "SELECT COUNT(*) FROM books;"
#define SELECTALLWHEREID "SELECT * FROM books WHERE ID="
#define INSERTVALUES "INSERT INTO books (call_number, author, title, edition, publication_location, publisher, publication_date, series_title, notes, isbn, subject) VALUES"

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

char** index_id_map;
char* book_columns[NUMCOLUMNS];

struct items_builder {
  int count;
  ITEM** items;
};

struct book {
  char* call_number;
  char* author;
  char* title;
  char* edition;
  char* publication_location;
  char* publisher;
  int publication_date;
  char* series_title;
  char* notes;
  int isbn;
  char* subject;
};


void init_book_columns(void);

// accessors/mutators
void add_item(sqlite3*, struct book*);
void edit_item(void);
void delete_item(void);
ITEM** get_item_info(sqlite3*, int);
ITEM** get_items(sqlite3*);