#include <gtk/gtk.h>
#include <regex.h>

static void on_check_button_clicked(GtkButton *button, gpointer user_data);
static int calculate_password_strength(const char *password);

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Password Strength Checker");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 200);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    GtkWidget *prompt_label = gtk_label_new("Enter a password between 8-32 characters:");
    gtk_grid_attach(GTK_GRID(grid), prompt_label, 0, 0, 1, 1);

    GtkWidget *password_entry = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(password_entry), FALSE);
    gtk_grid_attach(GTK_GRID(grid), password_entry, 0, 1, 1, 1);

    GtkWidget *check_button = gtk_button_new_with_label("Check Strength");
    gtk_grid_attach(GTK_GRID(grid), check_button, 0, 2, 1, 1);

    GtkWidget *result_label = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid), result_label, 0, 3, 1, 1);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(check_button, "clicked", G_CALLBACK(on_check_button_clicked), result_label);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}

static void on_check_button_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *result_label = GTK_WIDGET(user_data);
    GtkWidget *password_entry = gtk_bin_get_child(GTK_BIN(gtk_widget_get_parent(GTK_WIDGET(button))));

    const char *password = gtk_entry_get_text(GTK_ENTRY(password_entry));
    int strength_score = calculate_password_strength(password);

    char result_text[256];
    snprintf(result_text, sizeof(result_text), "Password: %s | Strength Score: %d/10", password, strength_score);
    gtk_label_set_text(GTK_LABEL(result_label), result_text);
}

static int calculate_password_strength(const char *password) {
    int length = strlen(password);

    if (length < 8 || length > 32) {
        return 0;
    }

    int score = 0;
    regex_t regex;

    if (length >= 8) score++;
    if (length >= 12) score++;
    if (length >= 16) score++;

    if (regcomp(&regex, "[a-z]", 0) == 0 && regexec(&regex, password, 0, NULL, 0) == 0) score++;
    regfree(&regex);

    if (regcomp(&regex, "[A-Z]", 0) == 0 && regexec(&regex, password, 0, NULL, 0) == 0) score++;
    regfree(&regex);

    if (regcomp(&regex, "[0-9]", 0) == 0 && regexec(&regex, password, 0, NULL, 0) == 0) score++;
    regfree(&regex);

    if (regcomp(&regex, "[!@#$%^&*()]", 0) == 0 && regexec(&regex, password, 0, NULL, 0) == 0) score++;
    regfree(&regex);

    if (length >= 12 && regcomp(&regex, "[a-z]", 0) == 0 && regexec(&regex, password, 0, NULL, 0) == 0 &&
        regcomp(&regex, "[A-Z]", 0) == 0 && regexec(&regex, password, 0, NULL, 0) == 0 &&
        regcomp(&regex, "[0-9]", 0) == 0 && regexec(&regex, password, 0, NULL, 0) == 0 &&
        regcomp(&regex, "[!@#$%^&*()]", 0) == 0 && regexec(&regex, password, 0, NULL, 0) == 0) {
        score++;
    }

    return score;
}
