/*
** EPITECH PROJECT, 2022
** my_chess
** File description:
** keys
*/

#include "chess.h"

void check_menu_player(config_t *config, game_t *game, int y, int x)
{
    if (y == config->yx_menu.y0 && x == config->yx_menu.x0 && config->player != 0) {
        config->player = 0;
        game->state = CLEAR_MENU_STATE;
    }
    if (y == config->yx_menu.y1 && x == config->yx_menu.x1 && config->player != 1) {
        config->player = 1;
        game->state = CLEAR_MENU_STATE;
    }
    if (y == config->yx_menu.y2 && x == config->yx_menu.x2 && config->player != 2) {
        config->player = 2;
        game->state = CLEAR_MENU_STATE;
    }
}

void check_menu_placement(config_t *config, game_t *game, int y)
{
    if (y == config->yx_menu.y_default && config->state != DEFAULT_CONFIG) {
        config->state = DEFAULT_CONFIG;
        game->state = CLEAR_MENU_STATE;
    }
    if (y == config->yx_menu.y_custom && config->state != CUSTOM_CONFIG) {
        config->state = CUSTOM_CONFIG;
        game->state = CLEAR_MENU_STATE;
    }
}

void check_menu_play(config_t *config, game_t *game, int y)
{
    if (y == config->yx_menu.y_play) {
        game->state = CLEAR_GAME_STATE;
    }
}

void check_game_case(config_t *config, game_t *game, MEVENT event, char color)
{
    int normalize_y = event.y / config->y_case_size;
    int normalize_x = event.x / config->x_case_size;

    if (normalize_y >= array_len(config->placement) || normalize_x > (int)strlen(config->placement[0]))
        return;
    attron(YLLW_ON_BLCK);
    if (config->placement[normalize_y][normalize_x * 2] != '-' &&
        config->placement[normalize_y][normalize_x * 2 + 1] == color) {
        game->turn = highlight_piece(*config, game, normalize_y, normalize_x);
    // } else if (game->turn == SELECT_DEST) {
    //     game->turn = 
    } else {
        print_pieces(*config);
        game->turn = SELECT_PIECE;
    }
}


void manage_key_mouse(config_t *config, game_t *game)
{
    MEVENT event;

    if (getmouse(&event) == OK && event.bstate & BUTTON1_PRESSED) {
        if (game->state == MENU_STATE) {
            check_menu_player(config, game, event.y, event.x);
            check_menu_placement(config, game, event.y);
            check_menu_play(config, game, event.y);
        }
        if (game->state == GAME_STATE_W) {
            check_game_case(config, game, event, 'w');
        }
        if (game->state == GAME_STATE_B) {
            check_game_case(config, game, event, 'b');
        }
    }
}
