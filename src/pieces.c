/*
** EPITECH PROJECT, 2022
** my_chess
** File description:
** pieces
*/

#include "chess.h"

piece_t get_piece_at(piece_t *pieces, int y, int x)
{
    int k = 0;

    for (k = 0; pieces[k].ressource != NULL; k++) {
        if (pieces[k].y == y && pieces[k].x == x)
            return (pieces[k]);
    }
    return pieces[k];
}

void print_piece(piece_t piece)
{
    int case_x_len = strlen(piece.ressource[0]) / 2;
    int case_y_len = array_len(piece.ressource) / 2;
    int y_offset = 0;
    int x_offset = 0;

    if (piece.color == 'w') {
        y_offset += case_y_len;
        if (piece.y % 2 == piece.x % 2)
            x_offset += case_x_len;
    } else {
        if (piece.y % 2 != piece.x % 2)
            x_offset += case_x_len;
    }
    for (int y = 0; y != case_y_len; y++)
        for (int x = 0; x != case_x_len; x++)
            mvprintw(case_y_len * piece.y + y, case_x_len * piece.x + x, "%c", piece.ressource[y + y_offset][x + x_offset]);
}

int nb_pieces(char *pieces, config_t config)
{
    int nb_pieces = 0;

    for (int i = 0; i != config.board_size; i++) {
        for (int j = 0; j != config.board_size * 2; j++) {
            for (int k = 0; pieces[k] != '\0'; k++) {
                if (config.board[i][j] == pieces[k])
                    nb_pieces++;
            }
        }
    }
    return nb_pieces;
}

game_t set_pieces(config_t config, game_t game)
{
    char *pieces = strdup("PRNBKQ");
    void *piece_ressource[6] = {PAWN, ROCK, KNIGHT, BISHOP, KING, QUEEN};
    void *piece_move[6] = {&pawn_move, &pawn_move, &pawn_move, &pawn_move, &pawn_move, &pawn_move};
    void *piece_highlight[6] = {&pawn_highlight, &pawn_highlight, &pawn_highlight, &pawn_highlight, &pawn_highlight, &pawn_highlight};
    char *ressource = NULL;
    int p = 0;

    game.pieces = malloc(sizeof(piece_t) * (nb_pieces(pieces, config) + 1));
    for (int i = 0; i != config.board_size; i++) {
        for (int j = 0; j != config.board_size * 2; j++) {
            for (int k = 0; pieces[k] != '\0'; k++) {
                if (config.board[i][j] == pieces[k]) {
                    game.pieces[p].y = i;
                    game.pieces[p].x = j / 2;
                    game.pieces[p].piece = pieces[k];
                    game.pieces[p].color = config.board[i][j + 1];
                    ressource = open_read_file(piece_ressource[k]);
                    game.pieces[p].ressource = explode(ressource, '\n');
                    game.pieces[p].p_highlight = piece_highlight[k];
                    game.pieces[p].p_move = piece_move[k];
                    game.pieces[p].possible_moves = NULL;
                    p++;
                }
            }
        }
    }
    game.pieces[p].ressource = NULL;
    free(pieces);
    free(ressource);
    return (game);
}