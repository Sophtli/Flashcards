#include <gtk/gtk.h>
#include <adwaita.h>

#include "flashcardsapp.h"
#include "flashcardsappwin.h"

struct _FlashcardsAppWindow
{
    AdwApplicationWindow parent;

    GtkWidget *topics;
};

G_DEFINE_TYPE(FlashcardsAppWindow, flashcards_app_window, ADW_TYPE_APPLICATION_WINDOW);

static void
flashcards_app_window_init(FlashcardsAppWindow *win)
{
    gtk_widget_init_template(GTK_WIDGET(win));
}

static void
flashcards_app_window_class_init(FlashcardsAppWindowClass *class)
{
    gtk_widget_class_set_template_from_resource(GTK_WIDGET_CLASS(class),
                                                "/li/sopht/flashcards/window.ui");

    gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (class), FlashcardsAppWindow, topics);
}

FlashcardsAppWindow *
flashcards_app_window_new(FlashcardsApp *app)
{
    return g_object_new(FLASHCARDS_APP_WINDOW_TYPE, "application", app, NULL);
}

void flashcards_app_window_open(FlashcardsAppWindow *win,
                                GFile *file)
{
}
