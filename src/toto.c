/*
** EPITECH PROJECT, 2022
** my_chess
** File description:
** toto
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    char *str = NULL;
    asprintf(&str, "%d-%d", 10, 5);
    printf("%s\n", strstr(str, "-") + 1);
    printf("%d\n", atoi(str));
    printf("%d\n", atoi(strstr(str, "-") + 1));
}