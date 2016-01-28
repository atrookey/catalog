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

void add_item()
{
  return;
}

void edit_item()
{
  return;
}

void delete_item()
{
  return;
}

ITEM* get_item()
{
  return NULL;
}

static int count_all_callback(void* void_count, int argc, char **argv, char **azColName) {
  int* count = (int*) void_count;

  // assert when you're not so lazy
  if (argc == 1) {
    *count = strtol(argv[0], NULL, 10);
  } else {
    return 1;
  }
  return 0;
}

static int select_all_callback(void* void_items_builder, int argc, char **argv, char **azColName) {
  struct items_builder* items_builder = (struct items_builder*) void_items_builder;
  if (argc < 4) {
    fprintf(stderr, "Umm so argc is %d\n", argc);
    return 1;
  }
  items_builder -> items[items_builder -> count] = new_item(strdup(argv[2]), strdup(argv[3]));
  items_builder -> count++;
  return 0;
}

ITEM** get_items(sqlite3 *db)
{
  int rc;
  int count;
  char *zErrMsg = NULL;
  struct items_builder items_builder;
  rc = sqlite3_exec(db, COUNTALL, count_all_callback, (void*) &count, &zErrMsg);
  if (rc!=SQLITE_OK) {
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  }
  items_builder = (struct items_builder) { 0, malloc(sizeof(ITEM*)*count+1) };
  items_builder.items[count] = NULL;
  rc = sqlite3_exec(db, SELECTALL, select_all_callback, (void*) &items_builder, &zErrMsg);
  if (rc!=SQLITE_OK) {
    fprintf(stderr, "SQL error: %s count: %d\n", zErrMsg, items_builder.count);
    sqlite3_free(zErrMsg);
  }
  return items_builder.items;
}