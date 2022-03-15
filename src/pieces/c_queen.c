/*
** EPITECH PROJECT, 2022
** my_chess
** File description:
** queen
*/

#include "chess.h"

// char **check_queen_spc(config_t config, game_t game, char **possibilities, int *i)
// {
//     char color = game.selected_piece[0];
//     int y = config.board_size - atoi(game.selected_piece + 2);
//     int x = (game.selected_piece[1] - 'A') * 2;
//     int direction = (color == 'w') ? -1 : 1;

//     return possibilities;
// }

char **check_queen_move(piece_t piece, config_t config)
{
    char **possibilities = NULL;
    int directions[16] = { 1, 0, -1, 0, 0, 1, 0, -1, 1, 1, -1, 1, 1, -1, -1, -1 };
    int i = 0;

    possibilities = malloc(sizeof(char *) * (config.board_size * 4));
    for (int k = 0; k < 16; k += 2) {
        for (int mul = 1; mul < config.board_size; mul++) {
            if ((piece.y + directions[k] * mul >= 0 && piece.y + directions[k] * mul < config.board_size) &&
                (piece.x + directions[k + 1] * mul >= 0 && piece.x + directions[k + 1] * mul < config.board_size)) {
                if (config.board[piece.y + directions[k] * mul][(piece.x + directions[k + 1] * mul) * 2] == '-') {
                    asprintf(&possibilities[i++], "%d%d", piece.y + directions[k] * mul, piece.x + directions[k + 1] * mul);
                } else if (config.board[piece.y + directions[k] * mul][(piece.x + directions[k + 1] * mul) * 2 + 1] != piece.color) {
                    asprintf(&possibilities[i++], "%d%d", piece.y + directions[k] * mul, piece.x + directions[k + 1] * mul);
                    break;
                } else
                    break;
            }
        }
    }
    possibilities[i] = NULL;
    return possibilities;
}

void queen_highlight(chess_t *chess)
{
    if (chess->game.selected_piece.possible_moves == NULL)
        chess->game.selected_piece.possible_moves = check_queen_move(chess->game.selected_piece, chess->config);
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

void queen_move(chess_t *chess, int y, int x)
{
    print_board_at(chess->config, chess->game.selected_piece.y, chess->game.selected_piece.x);
    chess->config.board[chess->game.selected_piece.y][chess->game.selected_piece.x * 2] = '-';
    chess->config.board[chess->game.selected_piece.y][chess->game.selected_piece.x * 2 + 1] = '-';
    update_pieces_from_selected(chess, y, x);
    chess->config.board[y][x * 2] = chess->game.selected_piece.piece;
    chess->config.board[y][x * 2 + 1] = chess->game.selected_piece.color;
}