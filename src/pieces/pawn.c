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

char **check_pawn_atk(config_t config, game_t game, char **possibilities, int *i)
{
    char color = game.selected_piece.color;
    int y = game.selected_piece.y;
    int x = game.selected_piece.x * 2;
    int direction = (color == 'w') ? -1 : 1;

    if (x > 1 &&
        config.board[y + direction][x - 2 + 1] != color &&
        config.board[y + direction][x - 2] != '-')
        asprintf(&possibilities[(*i)++], "%d%d", y + direction, (x - 2) / 2);
    if (x < (config.board_size - 1) * 2 &&
        config.board[y + direction][x + 2 + 1] != color &&
        config.board[y + direction][x + 2] != '-')
        asprintf(&possibilities[(*i)++], "%d%d", y + direction, (x + 2) / 2);
    possibilities[*i] = NULL;
    return possibilities;
}

char **check_pawn_move(config_t config, game_t game)
{
    char color = game.selected_piece.color;
    int y = game.selected_piece.y;
    int x = game.selected_piece.x * 2;
    int direction = (color == 'w') ? -1 : 1;
    char **possibilities = NULL;
    int i = 0;

    possibilities = malloc(sizeof(char *) * 5);
    if (config.board[y + direction][x] == '-')
        asprintf(&possibilities[i++], "%d%d", y + direction, x / 2);
    if ((color == 'w' && y == config.board_size - 2) || (color == 'b' && y == 1)) {
        if (config.board[y+ direction][x] == '-' &&
            config.board[y + direction * 2][x] == '-')
            asprintf(&possibilities[i++], "%d%d", y + direction * 2, x / 2);
    }
    possibilities[i] = NULL;
    return check_pawn_atk(config, game, possibilities, &i);
}

void *pawn_highlight(chess_t *chess)
{
    if (chess->game.selected_piece.possible_moves == NULL)
        chess->game.selected_piece.possible_moves = check_pawn_move(chess->config, chess->game);
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

void *pawn_move(chess_t *chess)
{
    (void)chess;
}