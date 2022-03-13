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

    game.pieces = NULL;
    game.history = NULL;
    game.selected_piece.ressource = NULL;
    game.turn = SELECT_PIECE;
    return (game);
}

void clear_highlight(config_t config, game_t *game)
{
    if (game->selected_piece.ressource == NULL || game->selected_piece.possible_moves == NULL)
        return;
    attron(YLLW_ON_BLCK);
    print_piece(game->selected_piece);
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

e_turn highlight_piece(chess_t *chess, int normalize_y, int normalize_x)
{
    // mvprintw(0, 0, "%d-%d", normalize_y, normalize_x);
    // char click = chess->config.board[normalize_y][normalize_x * 2];
    // char color_click = chess->config.board[normalize_y][normalize_x * 2 + 1];
    // char *pieces = strdup("P");
    // int (* piece_move[1])(config_t, game_t) = {&pawn_move};

    attron(BLCK_ON_MGNT);
    print_piece(chess->game.selected_piece);
    chess->game.selected_piece.p_highlight(chess);

    // for (int k = 0; chess->game.pieces[k].ressource != NULL; k++)
    //     print_piece(chess->game.pieces[k]);
    // print_piece(chess->game.pieces[]);
    // asprintf(&game->selected_piece, "%c%c%d", color_click, 'A' + normalize_x, config.board_size - normalize_y);
    // for (int i = 0; pieces[i] != '\0'; i++)
    //     if (pieces[i] == click)
    //         is_blocked = piece_move[i](config, *game);
    // free(pieces);
    if (chess->game.selected_piece.possible_moves == NULL)
        return SELECT_PIECE;
    return SELECT_DEST;
}