#include <gtk/gtk.h>
#include <adwaita.h>

#include "flashcardsapp.h"
#include "flashcardsappwin.h"

#include "database.h"

struct _FlashcardsAppWindow
{
    AdwApplicationWindow parent;

    FlashcardsApp* categories;

    GtkWidget* topics;
};

G_DEFINE_TYPE(FlashcardsAppWindow, flashcards_app_window, ADW_TYPE_APPLICATION_WINDOW);

static void
flashcards_app_window_init(FlashcardsAppWindow *win)
{
    gtk_widget_init_template(GTK_WIDGET(win));

    database_connect (g_get_user_data_dir());
    database_create_tables();
    win->categories = database_load_categories();
    
    GArray* categories = win->categories;

    for (int i = 0; i < categories->len; i++)
    {
        category c = g_array_index(categories, category, i);
        printf ("%d: %s\n", c.id, c.name);

        GtkWidget* child = adw_action_row_new();
        adw_preferences_row_set_title (ADW_PREFERENCES_ROW (child), c.name);

        gtk_list_box_append(GTK_LIST_BOX(win->topics), child);
    }
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
