#include <gtk/gtk.h>

#include "flashcardsapp.h"

int
main (int argc, char *argv[])
{
  return g_application_run (G_APPLICATION (flashcards_app_new ()), argc, argv);
}