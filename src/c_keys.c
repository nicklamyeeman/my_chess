/*
** EPITECH PROJECT, 2022
** my_chess
** File description:
** keys
*/

#include "chess.h"

void check_menu_player(chess_t *chess, int y, int x)
{
    if (y == chess->menu.y0 && x == chess->menu.x0 && chess->config.nb_player != 0) {
        chess->config.nb_player = 0;
        chess->state = CLEAR_MENU_STATE;
    }
    if (y == chess->menu.y1 && x == chess->menu.x1 && chess->config.nb_player != 1) {
        chess->config.nb_player = 1;
        chess->state = CLEAR_MENU_STATE;
    }
    if (y == chess->menu.y2 && x == chess->menu.x2 && chess->config.nb_player != 2) {
        chess->config.nb_player = 2;
        chess->state = CLEAR_MENU_STATE;
    }
}

void check_menu_placement(chess_t *chess, int y)
{
    if (y == chess->menu.y_default && chess->config.config != DEFAULT_CONFIG) {
        chess->config.config = DEFAULT_CONFIG;
        chess->state = CLEAR_MENU_STATE;
    }
    if (y == chess->menu.y_custom && chess->config.config != CUSTOM_CONFIG) {
        chess->config.config = CUSTOM_CONFIG;
        chess->state = CLEAR_MENU_STATE;
    }
}

void check_menu_play(chess_t *chess, int y)
{
    if (y == chess->menu.y_play) {
        chess->state = INIT_GAME_STATE;
    }
}

void check_game_case(chess_t *chess, MEVENT event, char color)
{
    int normalize_y = event.y / chess->config.case_size[0];
    int normalize_x = event.x / chess->config.case_size[1];
    piece_t piece = get_piece_at(chess->game.pieces, normalize_y, normalize_x);

    if (piece.ressource == NULL) {
        if (chess->game.turn == SELECT_PIECE) {
            (chess->game.selected_piece.ressource != NULL) ? clear_highlight(chess->config, &(chess->game)) : 0;
        } else {
            chess->game.turn = (chess->game.selected_piece.ressource != NULL) ? move_piece(chess, normalize_y, normalize_x) : chess->game.turn;
        }
    } else if (piece.color == color) {
        clear_highlight(chess->config, &(chess->game));
        chess->game.selected_piece = piece;
        chess->game.turn = highlight_piece(chess);
    } else {
        if (chess->game.turn == SELECT_PIECE) {
            (chess->game.selected_piece.ressource != NULL) ? clear_highlight(chess->config, &(chess->game)) : 0;
        } else {
            chess->game.turn = (chess->game.selected_piece.ressource != NULL) ? move_piece(chess, normalize_y, normalize_x) : chess->game.turn;
        }
    }
}

void manage_key_mouse(chess_t *chess)
{
    MEVENT event;

    if (getmouse(&event) == OK &&
        (event.bstate & BUTTON1_PRESSED || event.bstate & BUTTON1_CLICKED)) {
        if (chess->state == MENU_STATE) {
            check_menu_player(chess, event.y, event.x);
            check_menu_placement(chess, event.y);
            check_menu_play(chess, event.y);
        }
        if (chess->state == GAME_STATE_W) {
            check_game_case(chess, event, 'w');
        }
        if (chess->state == GAME_STATE_B) {
            check_game_case(chess, event, 'b');
        }
    }
}
