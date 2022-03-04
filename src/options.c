/*
** EPITECH PROJECT, 2022
** my_chess
** File description:
** options
*/

#include "chess.h"

void color_options(void)
{
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_YELLOW);
}

void options(void)
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
    color_options();
    curs_set(0);
}