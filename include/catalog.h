//
//  catalog.h
//  Rookey Catalog
//
//  Created by Alexander Rookey on 1/27/16.
//  Copyright © 2016 Alexander Rookey. All rights reserved.
//

#define SELECTALL "SELECT * FROM books;"
#define COUNTALL "SELECT COUNT(*) FROM books;"

struct items_builder {
  int count;
  ITEM** items;
};

void add_item(void);
void edit_item(void);
void delete_item(void);
ITEM* get_item(void);
ITEM** get_items(sqlite3*);