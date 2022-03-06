/*
** EPITECH PROJECT, 2022
** my_chess
** File description:
** pieces
*/

#include "chess.h"

void load_print_piece(char *assetpath, int i, int j, char color)
{
    char *piece_buffer = open_read_file(assetpath);
    char **piece = explode(piece_buffer, '\n');
    int case_x_len = strlen(piece[0]) / 2;
    int case_y_len = array_len(piece) / 2;
    int y_offset = 0;
    int x_offset = 0;

    if (color == 'w') {
        y_offset += case_y_len;
        if ((i % 2 == 0 && j % 2 == 0) ||
            (i % 2 == 1 && j % 2 == 1))
            x_offset += case_x_len;
    } else {
        if ((i % 2 == 1 && j % 2 == 0) ||
            (i % 2 == 0 && j % 2 == 1))
            x_offset += case_x_len;
    }
    for (int y = 0; y != case_y_len; y++)
        for (int x = 0; x != case_x_len; x++)
            mvprintw(case_y_len * i + y, case_x_len * j + x, "%c", piece[y + y_offset][x + x_offset]);
    free_ressource(piece_buffer, piece);
}

void print_piece_at(int y, int x, char piece, char color)
{
    char *pieces = strdup("-PRNBKQ");
    void *piece_ressource[7] = {BOARD, PAWN, ROCK, KNIGHT, BISHOP, KING, QUEEN};

    for (int k = 0; pieces[k] != '\0'; k++)
        if (piece == pieces[k]) {
            load_print_piece(piece_ressource[k], y, x, color);
        }
    free(pieces);
}

void print_pieces(config_t config)
{
    for (int i = 0; config.placement[i] != NULL; i++)
        for (int j = 0; config.placement[i][j] != '\0'; j++)
            print_piece_at(i, j / 2, config.placement[i][j], config.placement[i][j + 1]);
}