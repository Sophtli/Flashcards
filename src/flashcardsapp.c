#include <gtk/gtk.h>
#include <adwaita.h>

#include "flashcardsapp.h"
#include "flashcardsappwin.h"

#include "database.h"

struct _FlashcardsApp
{
  AdwApplication parent;
};

G_DEFINE_TYPE(FlashcardsApp, flashcards_app, ADW_TYPE_APPLICATION);

static void
flashcards_app_init(FlashcardsApp *app)
{
}

static void
flashcards_app_activate(GApplication *app)
{
  FlashcardsAppWindow *win;

  database_connect(g_get_user_data_dir());
  database_create_tables();
  GArray *categories = database_load_categories();

  win = flashcards_app_window_new(FLASHCARDS_APP(app));
  gtk_window_present(GTK_WINDOW(win));
}

static void
flashcards_app_open(GApplication *app,
                    GFile **files,
                    int n_files,
                    const char *hint)
{
  GList *windows;
  FlashcardsAppWindow *win;
  int i;

  windows = gtk_application_get_windows(GTK_APPLICATION(app));
  if (windows)
    win = FLASHCARDS_APP_WINDOW(windows->data);
  else
    win = flashcards_app_window_new(FLASHCARDS_APP(app));

  for (i = 0; i < n_files; i++)
    flashcards_app_window_open(win, files[i]);

  gtk_window_present(GTK_WINDOW(win));
}

static void
flashcards_app_class_init(FlashcardsAppClass *class)
{
  G_APPLICATION_CLASS(class)->activate = flashcards_app_activate;
  G_APPLICATION_CLASS(class)->open = flashcards_app_open;
}

FlashcardsApp *
flashcards_app_new(void)
{
  return g_object_new(FLASHCARDS_APP_TYPE,
                      "application-id", "li.sopht.flashcards",
                      "flags", G_APPLICATION_HANDLES_OPEN,
                      NULL);
}
