/*
** EPITECH PROJECT, 2022
** my_chess
** File description:
** board
*/

#include "chess.h"

void free_board(char *board_buffer, char **board)
{
    free(board_buffer);
    for (int i = 0; board[i] != NULL; i++)
        free(board[i]);
    free(board);
}

void print_board(config_t config)
{
    char *board_buffer = open_read_file(BOARD);
    char **board = explode(board_buffer, '\n');
    int x_offset = strlen(board[0]);
    int y_offset = array_len(board);

    for (int y = 0; y < config.board_size / 2; y++) {
        for (int x = 0; x < config.board_size / 2; x++)
            for (int i = 0; board[i] != NULL; i++)
                mvprintw(y_offset * y + i, x_offset * x, "%s", board[i]);
        printw("\n");
    }
    free_board(board_buffer, board);
}