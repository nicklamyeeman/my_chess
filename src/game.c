/*
** EPITECH PROJECT, 2022
** my_chess
** File description:
** game
*/

#include "chess.h"

game_t init_game(void)
{
    game_t game;

    game.history = NULL;
    game.selected_piece = NULL;
    game.state = MENU_STATE;
    game.turn = SELECT_PIECE;
    return (game);
}

e_turn highlight_piece(config_t config, game_t *game, int normalize_y, int normalize_x)
{
    char click = config.placement[normalize_y][normalize_x * 2];
    char color_click = config.placement[normalize_y][normalize_x * 2 + 1];
    char *pieces = strdup("P");
    int (* piece_move[1])(config_t, game_t) = {&pawn_move};
    int is_blocked = 0;

    print_pieces(config);
    attron(BLCK_ON_MGNT);
    print_piece_at(normalize_y, normalize_x, click, color_click);
    asprintf(&game->selected_piece, "%c%c%d", color_click, 'A' + normalize_x, config.board_size - normalize_y);
    for (int i = 0; pieces[i] != '\0'; i++)
        if (pieces[i] == click)
            is_blocked = piece_move[i](config, *game);
    free(pieces);
    if (is_blocked)
        return SELECT_PIECE;
    return SELECT_DEST;
}