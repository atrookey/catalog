#define KEY_LINE_FEED 10
#define KEY_DELETE 127

int list_view(sqlite3*);
int book_view(sqlite3*, int);
int new_book_view(sqlite3*);
int edit_book_view(void);