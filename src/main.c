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

int main(int argc, const char * argv[])
{
  init_views();
  init_catalog();

  // open main page
  return list_view(); // calls endwin()
}
