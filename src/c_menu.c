/*
** EPITECH PROJECT, 2022
** my_chess
** File description:
** menu
*/

#include "c_chess.h"

menu_t get_yx_menu(menu_t yx_menu)
{
    for (int y = 0; yx_menu.menu[y] != NULL; y++) {
        for (int x = 0; yx_menu.menu[y][x]; x++) {
            if (yx_menu.menu[y][x] - '0' == 0) {
                yx_menu.y0 = y;
                yx_menu.x0 = x;
            } else if (yx_menu.menu[y][x] - '0' == 1) {
                yx_menu.y1 = y;
                yx_menu.x1 = x;
            } else if (yx_menu.menu[y][x] - '0' == 2) {
                yx_menu.y2 = y;
                yx_menu.x2 = x;
            } else if (strstr(yx_menu.menu[y], "DEFAULT") != NULL && yx_menu.y_default == -1)
                yx_menu.y_default = y;
            else if (strstr(yx_menu.menu[y], "CUSTOM") != NULL && yx_menu.y_custom == -1)
                yx_menu.y_custom = y;
            else if (strstr(yx_menu.menu[y], "START") != NULL && yx_menu.y_play == -1)
                yx_menu.y_play = y;
        }
    }
    return (yx_menu);
}

void menu_config(char **menu, int i, int j, config_t config)
{
    if (menu[i][j] - '0' == config.nb_player)
        attron(BLCK_ON_YLLW);
    else if (config.config == DEFAULT_CONFIG &&
            strstr(menu[i], "DEFAULT") != NULL && isalpha(menu[i][j]))
        attron(BLCK_ON_YLLW);
    else if (config.config == CUSTOM_CONFIG &&
            strstr(menu[i], "CUSTOM") != NULL && isalpha(menu[i][j]))
        attron(BLCK_ON_YLLW);
    else
        attron(YLLW_ON_BLCK);
}

void print_menu(menu_t menu, config_t config)
{
    for (int i = 0; menu.menu[i] != NULL; i++) {
        for (int j = 0; menu.menu[i][j] != '\0'; j++) {
            menu_config(menu.menu, i, j, config);
            printw("%c", menu.menu[i][j]);
        }
        printw("\n");
    }
}

menu_t init_menu(void)
{
    menu_t yx_menu;
    char *menu_buffer = open_read_file(MENU);

    yx_menu.menu = explode(menu_buffer, '\n');
    yx_menu.y0 = yx_menu.x0 = -1;
    yx_menu.y1 = yx_menu.x1 = -1;
    yx_menu.y2 = yx_menu.x2 = -1;
    yx_menu.y_default = -1;
    yx_menu.y_custom = -1;
    yx_menu.y_play = -1;
    yx_menu = get_yx_menu(yx_menu);
    free(menu_buffer);
    return yx_menu;
}