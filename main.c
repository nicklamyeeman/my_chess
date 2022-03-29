/*
** EPITECH PROJECT, 2022
** my_chess
** File description:
** main
*/

#include "c_chess.h"

int main(int ac, char **av)
{
    if (ac == 2 &&
        (strcmp("-h", av[1]) == 0 || strcmp("--help", av[1]) == 0))
        return (usage(0));
    if (ac != 1)
        return (usage(84));
    return my_chess();
}