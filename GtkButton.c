#include <gtk/gtk.h>

void btn_clicked(GtkButton *self, gpointer data) {
  g_print("You clicked me!\n");
}

void app_startup(GApplication *self, gpointer data) {
  GtkWidget *win = g_object_new(
    GTK_TYPE_APPLICATION_WINDOW,
    "application", self,
    "default-width", 400,
    "default-height", 400,
    NULL
  );

  GtkWidget *header = g_object_new(
    GTK_TYPE_HEADER_BAR,
    "visible", TRUE,
    "show-close-button", TRUE,
    "title", "GtkButton",
    NULL
  );

  GtkWidget *btn = g_object_new(
    GTK_TYPE_BUTTON,
    "visible", TRUE,
    "label", "Click me!",
    "halign", GTK_ALIGN_CENTER,
    "valign", GTK_ALIGN_CENTER,
    NULL
  );

  g_signal_connect(btn, "clicked", G_CALLBACK(btn_clicked), NULL);

  gtk_container_add(GTK_CONTAINER(win), btn);
  gtk_window_set_titlebar(GTK_WINDOW(win), header);
}

void app_activate(GtkApplication *self, gpointer data) {
  GtkWindow *win = gtk_application_get_active_window(GTK_APPLICATION(self));
  gtk_window_present(win);
}

int main(int argc, char **argv) {
  GtkApplication *app = g_object_new(
    GTK_TYPE_APPLICATION,
    "application-id", "com.github.Miqueas.c-gtk-examples.GtkButton",
    "flags", G_APPLICATION_FLAGS_NONE,
    NULL
  );

  g_signal_connect(app, "startup",  G_CALLBACK(app_startup),  NULL);
  g_signal_connect(app, "activate", G_CALLBACK(app_activate), NULL);

  int res = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return res;
}