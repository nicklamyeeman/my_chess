/*
** EPITECH PROJECT, 2022
** my_chess
** File description:
** king
*/

#include "chess.h"

// char **check_king_spc(config_t config, game_t game, char **possibilities, int *i)
// {
// }

char **check_king_move(piece_t piece, config_t config)
{
    char **possibilities = NULL;
    int directions[16] = { 1, 0, 0, 1, -1, 0, 0, -1, 1, 1, -1, -1, 1, -1, -1, 1 };
    int i = 0;

    possibilities = malloc(sizeof(char *) * 9);
    for (int k = 0; k < 16; k += 2) {
        if ((piece.y + directions[k] >= 0 && piece.y + directions[k] < config.board_size) &&
            (piece.x + directions[k + 1] >= 0 && piece.x + directions[k + 1] < config.board_size) &&
            (config.board[piece.y + directions[k]][(piece.x + directions[k + 1]) * 2] == '-' ||
             config.board[piece.y + directions[k]][(piece.x + directions[k + 1]) * 2 + 1] != piece.color))
            asprintf(&possibilities[i++], "%d%d", piece.y + directions[k], piece.x + directions[k + 1]);
    }
    possibilities[i] = NULL;
    return possibilities;
}

void king_highlight(chess_t *chess)
{
    if (chess->game.selected_piece.possible_moves == NULL)
        chess->game.selected_piece.possible_moves = check_king_move(chess->game.selected_piece, chess->config);
    if (chess->game.selected_piece.possible_moves != NULL) {
        attron(BLCK_ON_CYAN);
        for (int i = 0; chess->game.selected_piece.possible_moves[i] != NULL; i++) {
            int y = chess->game.selected_piece.possible_moves[i][0] - '0';
            int x = chess->game.selected_piece.possible_moves[i][1] - '0';
            piece_t h_piece = get_piece_at(chess->game.pieces, y, x);
            if (h_piece.ressource == NULL)
                print_board_at(chess->config, y, x);
            else
                print_piece(h_piece);
        }
    }
}

void king_move(chess_t *chess)
{
    (void)chess;
}