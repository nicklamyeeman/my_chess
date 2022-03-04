/*
** EPITECH PROJECT, 2022
** my_chess
** File description:
** chess
*/

#include "chess.h"

e_state game_print(config_t config, e_state state)
{
    if (state == CLEAR_MENU_STATE) {
        clear();
        refresh();
        print_menu(config);
        return (MENU_STATE);
    }
    if (state == CLEAR_GAME_STATE) {
        clear();
        refresh();
        return (GAME_STATE);
    }
    return state;
}

void game_loop()
{
    e_state state = MENU_STATE;
    config_t config = init_config();
    int k = 0;

    options();
    print_menu(config);
    while (k != 27) {
        k = wgetch(stdscr);
        if (k == KEY_MOUSE)
            state = manage_key_mouse(&config, state);
        state = game_print(config, state);
    }
    endwin();
}

int my_chess()
{
    game_loop();
    return 0;
}