/*
** EPITECH PROJECT, 2022
** my_chess
** File description:
** keys
*/

#include "chess.h"

void check_player(e_state *state, config_t *config, int y, int x)
{
    if (y == config->yx_menu.y0 && x == config->yx_menu.x0 && config->player != 0) {
        config->player = 0;
        *state = CLEAR_MENU_STATE;
    }
    if (y == config->yx_menu.y1 && x == config->yx_menu.x1 && config->player != 1) {
        config->player = 1;
        *state = CLEAR_MENU_STATE;
    }
    if (y == config->yx_menu.y2 && x == config->yx_menu.x2 && config->player != 2) {
        config->player = 2;
        *state = CLEAR_MENU_STATE;
    }
}

void check_placement(e_state *state, config_t *config, int y)
{
    if (y == config->yx_menu.y_default && config->state != DEFAULT_CONFIG) {
        config->state = DEFAULT_CONFIG;
        *state = CLEAR_MENU_STATE;
    }
    if (y == config->yx_menu.y_custom && config->state != CUSTOM_CONFIG) {
        config->state = CUSTOM_CONFIG;
        *state = CLEAR_MENU_STATE;
    }
}

void check_play(e_state *state, config_t *config, int y)
{
    if (y == config->yx_menu.y_play) {
        *state = CLEAR_GAME_STATE;
    }
}

e_state manage_key_mouse(config_t *config, e_state state)
{
    MEVENT event;

    if (getmouse(&event) == OK && event.bstate & BUTTON1_PRESSED) {
        if (state == MENU_STATE) {
            check_player(&state, config, event.y, event.x);
            check_placement(&state, config, event.y);
            check_play(&state, config, event.y);
        }
    }
    return (state);
}
