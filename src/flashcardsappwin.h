#ifndef __FLASHCARDSAPPWIN_H
#define __FLASHCARDSAPPWIN_H

#include <gtk/gtk.h>
#include <adwaita.h>
#include "flashcardsapp.h"

#define FLASHCARDS_APP_WINDOW_TYPE (flashcards_app_window_get_type())
G_DECLARE_FINAL_TYPE(FlashcardsAppWindow, flashcards_app_window, FLASHCARDS, APP_WINDOW, AdwApplicationWindow)

FlashcardsAppWindow *flashcards_app_window_new(FlashcardsApp *app);
void flashcards_app_window_open(FlashcardsAppWindow *win,
                                GFile *file);

#endif /* __FLASHCARDSAPPWIN_H */
