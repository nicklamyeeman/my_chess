/*
** EPITECH PROJECT, 2022
** my_chess
** File description:
** pieces
*/

#include "chess.h"

void free_piece(char *piece_buffer, char **piece)
{
    free(piece_buffer);
    for (int i = 0; piece[i] != NULL; i++)
        free(piece[i]);
    free(piece);
}

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
    for (int y = 0; y != case_y_len; y++) {
        for (int x = 0; x != case_x_len; x++)
            mvprintw(case_y_len * i + y, case_x_len * j + x, "%c", piece[y + y_offset][x + x_offset]);
        printw("\n");
    }
    free_piece(piece_buffer, piece);
}

void print_pieces(config_t config)
{
    for (int i = 0; i != config.board_size; i++) {
        for (int j = 0; j < config.board_size * 2; j++) {
            switch (config.placement[i][j]) {
                case 'b':
                    break;
                case 'w':
                    break;
                case 'P':
                    load_print_piece(PAWN, i, j / 2, config.placement[i][j + 1]);
                    break;
                case 'R':
                    load_print_piece(ROCK, i, j / 2, config.placement[i][j + 1]);
                    break;
                case 'N':
                    load_print_piece(KNIGHT, i, j / 2, config.placement[i][j + 1]);
                    break;
                case 'B':
                    load_print_piece(BISHOP, i, j / 2, config.placement[i][j + 1]);
                    break;
                case 'K':
                    load_print_piece(KING, i, j / 2, config.placement[i][j + 1]);
                    break;
                case 'Q':
                    load_print_piece(QUEEN, i, j / 2, config.placement[i][j + 1]);
                    break;
            }
        }
    }
}