#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>

struct Book {
    char title[20];
};

struct Book book;
struct Book books[100];

GtkWidget *en_title = NULL;
GtkWidget *en_id = NULL;
GtkWidget *textview = NULL;

int id;

static void printBook(int id)
{
    for(int i = 0; i <= id; i++){
        printf("Books: %s \n", books[i].title);
    }
}

static void read_from_file()
{
    FILE *fp;
    //char buff[255];
    int c;

    fp = fopen("books.txt", "r");
    //fgets(buff, 255, (FILE*)fp);
    //printf("%s", buff);
    if(fp){
        while((c = getc(fp)) != EOF)
            putchar(c);
        fclose(fp);
    }
}

static void write_to_file()
{
    FILE *fp;
    fp = fopen("books.txt", "a+");
    for(int i = 0; i <= id; i++){
        fprintf(fp, "%s \n", books[i].title);
    }
    fclose(fp);
}

static void adauga(void)
{

    id = atoi(gtk_entry_get_text(en_id));
    strcpy(book.title, gtk_entry_get_text(en_title));
    printf("Titlu: %s \n", book.title);
    //Adaugarea elementelor in array
    //for(int i = 0; i < id ; i++){
        books[id] = book;
    //}
    printBook(id);

    gtk_entry_set_text(en_title, "");
    id++;
    gchar id_char[64];
    sprintf(id_char, "%d", id);
    gtk_entry_set_text(en_id, id_char);

}

static void helloWorld (GtkWidget *wid, GtkWidget *win)
{
  GtkWidget *dialog = NULL;

  dialog = gtk_message_dialog_new (GTK_WINDOW (win), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE, "Hello World!");
  gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_CENTER);
  gtk_dialog_run (GTK_DIALOG (dialog));
  gtk_widget_destroy (dialog);
  read_from_file();
}

int main (int argc, char *argv[])
{
  GtkWidget *button = NULL;
  GtkWidget *bt_adauga = NULL;
  GtkWidget *bt_save = NULL;
  GtkWidget *win = NULL;
  GtkWidget *vbox = NULL;

  /* Initialize GTK+ */
  g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, (GLogFunc) gtk_false, NULL);
  gtk_init (&argc, &argv);
  g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, g_log_default_handler, NULL);

  /* Create the main window */
  win = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_container_set_border_width (GTK_CONTAINER (win), 8);
  gtk_window_set_title (GTK_WINDOW (win), "Hello World");
  gtk_window_set_position (GTK_WINDOW (win), GTK_WIN_POS_CENTER);
  gtk_widget_realize (win);
  g_signal_connect (win, "destroy", gtk_main_quit, NULL);

  /* Create a vertical box with buttons */
  vbox = gtk_vbox_new (TRUE, 6);
  gtk_container_add (GTK_CONTAINER (win), vbox);

  en_id = gtk_entry_new();
  gtk_box_pack_start (GTK_BOX (vbox), en_id, TRUE, TRUE, 0);

  en_title = gtk_entry_new();
  gtk_box_pack_start (GTK_BOX (vbox), en_title, TRUE, TRUE, 0);




  button = gtk_button_new_from_stock (GTK_STOCK_DIALOG_INFO);
  g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (helloWorld), (gpointer) win);
  gtk_box_pack_start (GTK_BOX (vbox), button, TRUE, TRUE, 0);

  button = gtk_button_new_from_stock (GTK_STOCK_CLOSE);
  g_signal_connect (button, "clicked", gtk_main_quit, NULL);
  gtk_box_pack_start (GTK_BOX (vbox), button, TRUE, TRUE, 0);

  bt_adauga = gtk_button_new_with_label("Adauga");
  g_signal_connect (bt_adauga, "clicked", adauga, NULL);
  gtk_box_pack_start (GTK_BOX (vbox), bt_adauga, TRUE, TRUE, 0);

  bt_save = gtk_button_new_with_label("Salveaza");
  g_signal_connect (bt_save, "clicked", write_to_file, NULL);
  gtk_box_pack_start (GTK_BOX (vbox), bt_save, TRUE, TRUE, 0);

  textview = gtk_text_view_new();
  gtk_box_pack_start (GTK_BOX (vbox), textview, TRUE, TRUE, 0);


  /* Enter the main loop */
  gtk_widget_show_all (win);
  gtk_main ();
  return 0;
}
