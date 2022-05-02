#define GETTEXT_PACKAGE "flashcards"

#include <gtk/gtk.h>
#include <glib/gi18n.h>
#include <locale.h>

#include "flashcardsapp.h"

int
main (int argc, char *argv[])
{
  setlocale (LC_ALL, "");
  bindtextdomain (GETTEXT_PACKAGE, "/usr/local/share/locale");
  bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
  textdomain (GETTEXT_PACKAGE);

  return g_application_run (G_APPLICATION (flashcards_app_new ()), argc, argv);
}