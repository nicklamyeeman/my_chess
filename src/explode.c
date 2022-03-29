/*
** EPITECH PROJECT, 2018
** my str to word array
** File description:
** str to word ta
*/

#include "c_chess.h"

int nb_line(char *str, char separator)
{
    int line = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == separator)
            line += 1;
    }
    return line;
}

char **malloc_array(char *str, char separator)
{
    char **array = malloc(sizeof(char *) * (nb_line(str, separator) + 1));
    int line = 0;
    int word_len = 1;

    for (int i = 0; str[i] != '\0'; i++, word_len++) {
        if (str[i] == separator) {
            array[line] = malloc(sizeof(char) * (word_len + 1));
            line += 1;
            word_len = 0;
        }
    }
    array[line] = NULL;
    return array;
}

char **explode(char *str, char separator)
{
    char **array = malloc_array(str, separator);

    for (int i = 0, col = 0, line = 0; str[i] != '\0'; i++, col++) {
        if (str[i] == separator) {
            array[line][col] = '\0';
            line += 1;
            col = -1;
        } else
            array[line][col] = str[i];
    }
    return array;
}