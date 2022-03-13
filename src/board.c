/*
** EPITECH PROJECT, 2022
** my_chess
** File description:
** board
*/

#include "chess.h"

void print_board_at(config_t config, int y, int x)
{
    int case_x_len = strlen(config.board_ressource[0]) / 2;
    int case_y_len = array_len(config.board_ressource) / 2;
    int x_offset = 0;

    if (y % 2 != x % 2)
        x_offset += case_x_len;
    for (int i = 0; i != case_y_len; i++)
        for (int j = 0; j != case_x_len; j++)
            mvprintw(case_y_len * y + i, case_x_len * x + j, "%c", config.board_ressource[i][j + x_offset]);
}

void print_board(config_t config)
{
    for (int y = 0; y < config.board_size; y++)
        for (int x = 0; x < config.board_size; x++)
            print_board_at(config, y, x);
}