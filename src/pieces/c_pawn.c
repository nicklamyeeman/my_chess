/*
** EPITECH PROJECT, 2022
** my_chess
** File description:
** pawn
*/

#include "chess.h"

// char **check_pawn_spc(config_t config, game_t game, char **possibilities, int *i)
// {
//     char color = game.selected_piece[0];
//     int y = config.board_size - atoi(game.selected_piece + 2);
//     int x = (game.selected_piece[1] - 'A') * 2;
//     int direction = (color == 'w') ? -1 : 1;

//     return possibilities;
// }

char **check_pawn_atk(piece_t piece, config_t config, char **possibilities, int *i)
{
    int direction = (piece.color == 'w') ? -1 : 1;

    if (piece.x * 2 > 1 &&
        config.board[piece.y + direction][piece.x * 2 - 2 + 1] != piece.color &&
        config.board[piece.y + direction][piece.x * 2 - 2] != '-')
        asprintf(&possibilities[(*i)++], "%d%d", piece.y + direction, (piece.x * 2 - 2) / 2);
    if (piece.x * 2 < (config.board_size - 1) * 2 &&
        config.board[piece.y + direction][piece.x * 2 + 2 + 1] != piece.color &&
        config.board[piece.y + direction][piece.x * 2 + 2] != '-')
        asprintf(&possibilities[(*i)++], "%d%d", piece.y + direction, (piece.x * 2 + 2) / 2);
    possibilities[*i] = NULL;
    if (*i == 0)
        return NULL;
    return possibilities;
}

char **check_pawn_move(piece_t piece, config_t config)
{
    int direction = (piece.color == 'w') ? -1 : 1;
    char **possibilities = NULL;
    int i = 0;

    possibilities = malloc(sizeof(char *) * 5);
    if (piece.y + direction > config.board_size || piece.y + direction < 0)
        return NULL;
    if (config.board[piece.y + direction][piece.x * 2] == '-')
        asprintf(&possibilities[i++], "%d%d", piece.y + direction, piece.x * 2 / 2);
    if ((piece.color == 'w' && piece.y == config.board_size - 2) || (piece.color == 'b' && piece.y == 1)) {
        if (config.board[piece.y+ direction][piece.x * 2] == '-' &&
            config.board[piece.y + direction * 2][piece.x * 2] == '-')
            asprintf(&possibilities[i++], "%d%d", piece.y + direction * 2, piece.x);
    }
    possibilities[i] = NULL;
    return check_pawn_atk(piece, config, possibilities, &i);
}

void pawn_highlight(chess_t *chess)
{
    if (chess->game.selected_piece.possible_moves == NULL)
        chess->game.selected_piece.possible_moves = check_pawn_move(chess->game.selected_piece, chess->config);
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

void pawn_move(chess_t *chess)
{
    chess->config.board[chess->game.selected_piece.y][chess->game.selected_piece.x * 2] = chess->game.selected_piece.piece;
    chess->config.board[chess->game.selected_piece.y][chess->game.selected_piece.x * 2 + 1] = chess->game.selected_piece.color;
}