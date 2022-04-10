#include <adwaita.h>

#include "database.c"

static void activate (GtkApplication *app)
{
    GtkWidget *window = gtk_application_window_new(app);

    // gtk_window_set_default_size (GTK_WINDOW(window), 200, 200);
    // gtk_window_set_child (GTK_WINDOW (window), label);

    GtkWidget *header_bar = adw_header_bar_new();
    GtkWidget *window_title = adw_window_title_new("Karteikarten", "Lernen mit Stil");
    adw_header_bar_set_title_widget(ADW_HEADER_BAR(header_bar), window_title);

    // gtk_window_set_titlebar (GTK_WINDOW(window), header_bar);

    GtkBuilder *list_builder = gtk_builder_new_from_file ("window.ui");

    gtk_window_set_titlebar (GTK_WINDOW (window), GTK_WIDGET (gtk_builder_get_object (list_builder, "leaflet")));

    // gtk_window_set_child (GTK_WINDOW (window), GTK_WIDGET (gtk_builder_get_object (list_builder, "list")));

    gtk_window_present (GTK_WINDOW (window));
}

int main (int argc, char *argv[])
{
    printf("%s\n", g_get_user_config_dir());
    printf("%s\n", g_get_user_data_dir());

    database_connect (g_get_user_data_dir());
    database_create_tables();
    GArray *categories = database_load_categories();
    for (int i = 0; i < categories->len; i++)
    {
        category c = g_array_index(categories, category, i);
        printf ("%d: %s\n", c.id, c.name);
    }

    g_autoptr(AdwApplication) app = NULL;

    app = adw_application_new("li.sopht.Flashcards", G_APPLICATION_FLAGS_NONE);

    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    return g_application_run(G_APPLICATION(app), argc, argv);
}
