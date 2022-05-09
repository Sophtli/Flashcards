#ifndef __FLASHCARDSAPP_H
#define __FLASHCARDSAPP_H

#include <gtk/gtk.h>
#include <adwaita.h>

#define FLASHCARDS_APP_TYPE (flashcards_app_get_type ())
G_DECLARE_FINAL_TYPE (FlashcardsApp, flashcards_app, FLASHCARDS, APP, AdwApplication)

FlashcardsApp     *flashcards_app_new         (void);

#endif /* __FLASHCARDSAPP_H */
