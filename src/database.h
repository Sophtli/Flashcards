#include <glib.h>

typedef struct category
{
    int id;
    char *name;
} category;

typedef struct card
{
    int category;
    char *task;
    char *solution;
} card;

void database_connect(const char *path);

void database_close();

void database_create_tables();

void database_save_category();

GArray* database_load_categories();

void database_save_card(card c);

card* database_load_cards();