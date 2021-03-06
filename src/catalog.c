//
//  catalog.c
//  Rookey Catalog
//
//  Created by Alexander Rookey on 1/27/16.
//  Copyright © 2016 Alexander Rookey. All rights reserved.
//

#include <menu.h>
#include <sqlite3.h>
#include <catalog.h>
#include <stdlib.h>
#include <string.h>

// database db should be static in this file.  That way I don't have to pass it
// around and it will make hooking into my forms easier

int init_catalog()
{
  int rc;

  // init database 
  rc = sqlite3_open(DBNAME, &db);
  if (rc){
    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return(1);
  }
  init_book_columns();
}

static int _insert_values_callback(void* NOTUSED, int argc, char **argv,
    char **azColName)
{
  return 0;
}

// this is gonna be turned into a hook that takes in a form
// db is now global
void add_item()
{
  int rc;
  char *zErrMsg = NULL;
  char sql[BUFSIZ];

  sprintf(sql, "%s ('%s', '%s', '%s', '%s', '%s', '%s', %d, '%s', '%s', %d, '%s');", 
      INSERTVALUES, new_book -> call_number, new_book -> author,
      new_book -> title, new_book -> edition, new_book -> publication_location,
      new_book -> publisher, new_book -> publication_date,
      new_book -> series_title, new_book -> notes, new_book -> isbn,
      new_book -> subject);
  rc = sqlite3_exec(db, sql, _insert_values_callback, NULL, &zErrMsg);
  if (rc!=SQLITE_OK) {
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  }
}

void edit_item()
{
  return;
}

void delete_item()
{
  return;
}

void init_book_columns()
{
  book_columns[ID] = strdup("ID");
  book_columns[CALLNUMBER] = strdup("CALL NUMBER");
  book_columns[AUTHOR] = strdup("AUTHOR");
  book_columns[TITLE] = strdup("TITLE");
  book_columns[EDITION] = strdup("EDITION");
  book_columns[PUBLICATIONLOCATION] = strdup("PUBLICATION LOCATION");
  book_columns[PUBLISHER] = strdup("PUBLISHER");
  book_columns[PUBLICATIONDATE] = strdup("PUBLICATION DATE");
  book_columns[SERIESTITLE] = strdup("SERIES TITLE");
  book_columns[NOTES] = strdup("NOTES");
  book_columns[ISBN] = strdup("ISBN");
  book_columns[SUBJECT] = strdup("SUBJECT");
}

static int _select_all_where_id_callback(void* untyped_items, int argc,
    char **argv, char **azColName)
{
  int i;
  ITEM** items;
  char* value;

  if (argc < NUMCOLUMNS || argc > NUMCOLUMNS) {
    fprintf(stderr, "Umm so argc is %d\n", argc);
    return 1;
  }

  // items = (ITEM***) untyped_items;
  items = malloc(sizeof(ITEM*)*argc+1);
  items[argc] = NULL;
  for (i = 0; i<argc; i++) {
    value = argv[i] ? argv[i] : NULLVALUE;
    items[i] = new_item(book_columns[i], strdup(value));
  }

  // don't understand how this works or doesn't work
  ITEM*** triple_items_ptr = untyped_items;
  *triple_items_ptr = items;
  return 0;
}

ITEM** get_item_info(int index)
{
  char* id;
  int rc;
  char *zErrMsg = NULL;
  char sql[BUFSIZ];
  ITEM** items;

  id = index_id_map[index];
  sprintf(sql, "%s%s;", SELECTALLWHEREID, index_id_map[index]);
  rc = sqlite3_exec(db, sql, _select_all_where_id_callback, &items, &zErrMsg);
  if (rc!=SQLITE_OK) {
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  }
  return items;
}

static int _count_all_callback(void* untyped_count, int argc, char **argv,
    char **azColName) 
{
  int* count = (int*) untyped_count;

  // assert when you're not so lazy
  if (argc == 1) {
    *count = strtol(argv[0], NULL, 10);
  } else {
    return 1;
  }
  return 0;
}

static int _select_all_callback(void* untyped_items_builder, int argc,
    char **argv, char **azColName)
{
  struct items_builder* items_builder;
  char* author;
  char* title;

  if (argc < NUMCOLUMNS || argc > NUMCOLUMNS) {
    fprintf(stderr, "Umm so argc is %d\n", argc);
    return 1;
  }
  items_builder = (struct items_builder*) untyped_items_builder;
  index_id_map[items_builder -> count] = strdup(argv[ID]);
  author = argv[AUTHOR] ? argv[AUTHOR] : NULLVALUE;
  title = argv[TITLE] ? argv[TITLE] : NULLVALUE;
  items_builder -> items[items_builder -> count] = new_item(strdup(author),
      strdup(title));
  items_builder -> count++;
  return 0;
}

ITEM** get_items()
{
  int rc;
  char *zErrMsg = NULL;
  int count;
  struct items_builder items_builder;
  rc = sqlite3_exec(db, COUNTALL, _count_all_callback, (void*) &count,
      &zErrMsg);
  if (rc!=SQLITE_OK) {
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  }
  index_id_map = malloc(sizeof(char*)*count); // should be created elsewhere
  items_builder = (struct items_builder) { 0, malloc(sizeof(ITEM*)*count+1) };
  items_builder.items[count] = NULL;
  rc = sqlite3_exec(db, SELECTALL, _select_all_callback, (void*) &items_builder,
      &zErrMsg);
  if (rc!=SQLITE_OK) {
    fprintf(stderr, "SQL error: %s count: %d\n", zErrMsg, items_builder.count);
    sqlite3_free(zErrMsg);
  }
  return items_builder.items;
}