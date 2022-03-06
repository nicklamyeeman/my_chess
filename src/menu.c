/*
** EPITECH PROJECT, 2022
** my_chess
** File description:
** menu
*/

#include "chess.h"

menu_t get_yx_menu(char **menu)
{
    menu_t yx_menu = {-1, -1, -1, -1, -1, -1, -1, -1, -1};

    for (int y = 0; menu[y] != NULL; y++) {
        for (int x = 0; menu[y][x]; x++) {
            if (menu[y][x] - '0' == 0) {
                yx_menu.y0 = y;
                yx_menu.x0 = x;
            } else if (menu[y][x] - '0' == 1) {
                yx_menu.y1 = y;
                yx_menu.x1 = x;
            } else if (menu[y][x] - '0' == 2) {
                yx_menu.y2 = y;
                yx_menu.x2 = x;
            } else if (strstr(menu[y], "DEFAULT") != NULL && yx_menu.y_default == -1)
                yx_menu.y_default = y;
            else if (strstr(menu[y], "CUSTOM") != NULL && yx_menu.y_custom == -1)
                yx_menu.y_custom = y;
            else if (strstr(menu[y], "START") != NULL && yx_menu.y_play == -1)
                yx_menu.y_play = y;
        }
    }
    return yx_menu;
}

void menu_config(char **menu, int i, int j, config_t config)
{
    if (menu[i][j] - '0' == config.player)
        attron(BLCK_ON_YLLW);
    else if (config.state == DEFAULT_CONFIG && strstr(menu[i], "DEFAULT") != NULL && isalpha(menu[i][j]))
        attron(BLCK_ON_YLLW);
    else if (config.state == CUSTOM_CONFIG && strstr(menu[i], "CUSTOM") != NULL && isalpha(menu[i][j]))
        attron(BLCK_ON_YLLW);
    else
        attron(YLLW_ON_BLCK);
}

void print_menu(config_t config)
{
    char *menu_buffer = open_read_file(MENU);
    char **menu = explode(menu_buffer, '\n');

    for (int i = 0; menu[i] != NULL; i++) {
        for (int j = 0; menu[i][j] != '\0'; j++) {
            menu_config(menu, i, j, config);
            printw("%c", menu[i][j]);
        }
        printw("\n");
    }
    free_ressource(menu_buffer, menu);
}
