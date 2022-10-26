#include <gtk/gtk.h>
#include <adwaita.h>

#include "flashcardsapp.h"
#include "flashcardsappwin.h"

#include "database.h"

struct _FlashcardsAppWindow
{
    AdwApplicationWindow parent;

    GArray *categories;

    AdwLeaflet *leaflet;
    GtkButton *leaflet_previous;
    GtkListBox *topics;
};

G_DEFINE_TYPE(FlashcardsAppWindow, flashcards_app_window, ADW_TYPE_APPLICATION_WINDOW);

static void
on_category_selected(GtkListBox *box, GtkListBoxRow *row, gpointer user_data)
{
    if (row == NULL)
    {
        return;
    }
    printf("Test\n");
    FlashcardsAppWindow *win = FLASHCARDS_APP_WINDOW(gtk_widget_get_root(GTK_WIDGET(box)));
    adw_leaflet_navigate(win->leaflet, ADW_NAVIGATION_DIRECTION_FORWARD);

    int id = gtk_list_box_row_get_index(gtk_list_box_get_selected_row(win->topics));
    printf("%d\n", id);
}

static void
on_navigate_back(GtkButton *button, gpointer user_data)
{
    printf("Test2\n");
    FlashcardsAppWindow *win = FLASHCARDS_APP_WINDOW(gtk_widget_get_root(GTK_WIDGET(button)));
    gtk_list_box_unselect_all(win->topics);
    adw_leaflet_navigate(win->leaflet, ADW_NAVIGATION_DIRECTION_BACK);
}

static void
flashcards_app_window_init(FlashcardsAppWindow *win)
{
    gtk_widget_init_template(GTK_WIDGET(win));

    database_connect(g_get_user_data_dir());
    database_create_tables();
    win->categories = database_load_categories();

    GArray *categories = win->categories;

    for (int i = 0; i < categories->len; i++)
    {
        category c = g_array_index(categories, category, i);
        printf("%d: %s\n", c.id, c.name);

        GtkWidget *child = adw_action_row_new();
        adw_preferences_row_set_title(ADW_PREFERENCES_ROW(child), c.name);

        gtk_list_box_append(GTK_LIST_BOX(win->topics), child);
    }
}

static void
flashcards_app_window_class_init(FlashcardsAppWindowClass *class)
{
    gtk_widget_class_set_template_from_resource(GTK_WIDGET_CLASS(class), "/li/sopht/flashcards/window.ui");

    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(class), FlashcardsAppWindow, leaflet);
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(class), FlashcardsAppWindow, leaflet_previous);
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(class), FlashcardsAppWindow, topics);

    gtk_widget_class_bind_template_callback(GTK_WIDGET_CLASS(class), on_navigate_back);
    gtk_widget_class_bind_template_callback(GTK_WIDGET_CLASS(class), on_category_selected);
}

FlashcardsAppWindow *
flashcards_app_window_new(FlashcardsApp *app)
{
    return g_object_new(FLASHCARDS_APP_WINDOW_TYPE, "application", app, NULL);
}

void flashcards_app_window_open(FlashcardsAppWindow *win, GFile *file)
{
}
