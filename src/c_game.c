/*
** EPITECH PROJECT, 2022
** my_chess
** File description:
** game
*/

#include "c_chess.h"

game_t init_game(void)
{
    game_t game;

    game.king_threat.ressource = NULL;
    game.pieces = NULL;
    game.history = NULL;
    game.selected_piece.ressource = NULL;
    game.turn = SELECT_PIECE;
    return (game);
}

void clear_highlight(config_t config, game_t *game)
{
    if (game->selected_piece.ressource == NULL)
        return;
    attron(YLLW_ON_BLCK);
    print_piece(game->selected_piece);
    if (game->selected_piece.possible_moves == NULL)
        return;
    for (int k = 0; game->selected_piece.possible_moves[k] != NULL; k++) {
        int y = game->selected_piece.possible_moves[k][0] - '0';
        int x = game->selected_piece.possible_moves[k][1] - '0';
        piece_t h_piece = get_piece_at(game->pieces, y, x);
        if (h_piece.ressource == NULL)
            print_board_at(config, y, x);
        else
            print_piece(h_piece);
        free(game->selected_piece.possible_moves[k]);
    }
    free(game->selected_piece.possible_moves);
    game->selected_piece.possible_moves = NULL;
}

e_turn highlight_piece(chess_t *chess)
{
    attron(BLCK_ON_MGNT);
    print_piece(chess->game.selected_piece);
    chess->game.selected_piece.p_highlight(chess);
    if (chess->game.selected_piece.possible_moves == NULL)
        return SELECT_PIECE;
    return SELECT_DEST;
}

e_turn move_piece(chess_t *chess, int normalize_y, int normalize_x)
{
    attron(YLLW_ON_BLCK);
    for (int k = 0; chess->game.selected_piece.possible_moves[k] != NULL; k++) {
        if (chess->game.selected_piece.possible_moves[k][0] - '0' == normalize_y &&
            chess->game.selected_piece.possible_moves[k][1] - '0' == normalize_x) {
            chess->game.selected_piece.p_move(chess, normalize_y, normalize_x);
            return NEXT_TURN;
        }
    }
    return SELECT_PIECE;
}