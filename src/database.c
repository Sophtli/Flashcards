#include "database.h"

#include <stdio.h>
#include <sqlite3.h>

sqlite3 *db;

void database_connect(const char *path)
{
    // char *zErrMsg = 0;

    int rc;

    gchar *file = g_build_filename(path, "cards.db", NULL);
    rc = sqlite3_open(file, &db);

    if (rc)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }
    else
    {
        fprintf(stderr, "Opened database successfully\n");
    }
    g_free(file);
}

void database_close()
{
    sqlite3_close(db);
}

void database_create_tables()
{
    int rc;
    sqlite3_stmt *stmt;

    char *sql = "CREATE TABLE IF NOT EXISTS `cards` ("
                "`category`	INTEGER NOT NULL,"
                "`task`	TEXT NOT NULL,"
                "`solution`	TEXT NOT NULL"
                ")";

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    sql = "CREATE TABLE IF NOT EXISTS `categories` ("
          "`id`	INTEGER NOT NULL,"
          "`name`	TEXT NOT NULL,"
          "PRIMARY KEY(`id` AUTOINCREMENT)"
          ")";

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

void database_save_category()
{
}

GArray *database_load_categories()
{
    GArray *categories = g_array_new(TRUE, FALSE, sizeof(category));

    int rc;
    sqlite3_stmt *stmt;

    rc = sqlite3_prepare_v2(db, "SELECT * FROM categories", -1, &stmt, 0);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char *temp_name = sqlite3_column_text(stmt, 1);
        fprintf(stdout, "%d: %s\n", id, temp_name);

        char *name = g_new0(char, strlen(temp_name));
        strcpy(name, temp_name);
        category c = {id, name};
        g_array_append_val(categories, c);
    }

    sqlite3_finalize(stmt);
    return categories;
}

void database_save_card(card c)
{
    int rc;
    sqlite3_stmt *stmt;

    fprintf(stdout, "%s: %s\n", c.task, c.solution);
    rc = sqlite3_prepare_v2(db, "INSERT INTO cards VALUES(?, ?, ?)", -1, &stmt, 0);

    if (rc == SQLITE_OK)
    {
        sqlite3_bind_int(stmt, 0, c.category);
        sqlite3_bind_text(stmt, 1, c.task, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, c.solution, -1, SQLITE_STATIC);
    }
    else
    {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

GArray *database_load_cards()
{
    GArray *cards = g_array_new(TRUE, FALSE, sizeof(card));

    return cards;
}