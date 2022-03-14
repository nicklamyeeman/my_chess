/*
** EPITECH PROJECT, 2022
** my_chess
** File description:
** config
*/

#include "chess.h"

config_t init_config(void)
{
    char **map = malloc(sizeof(char *) * 9);
    map[0] = strdup("NwNbPwKbQbBbNbRb");
    map[1] = strdup("PbPbPbPbPbPbPbPb");
    map[2] = strdup("----PwQwKwPb----");
    map[3] = strdup("----------------");
    map[4] = strdup("--QwQw--------Nw");
    map[5] = strdup("--------Pw--Pb--");
    map[6] = strdup("PwPwPwPwPwPwPwPw");
    map[7] = strdup("RwNwBwKwQwBwNwRw");
    map[8] = NULL;

    config_t config = update_config(DEFAULT_CONFIG, 2, 8, map);
    return (config);
}

config_t update_config(e_config econfig, int nb_player, int board_size, char **map)
{
    char *board_buffer = open_read_file(BOARD);
    config_t config;
    int i = 0;

    config.config = econfig;
    config.nb_player = nb_player;
    config.board_size = board_size;
    config.board_ressource = explode(board_buffer, '\n');
    config.case_size[0] = array_len(config.board_ressource) / 2;
    config.case_size[1] = strlen(config.board_ressource[0]) / 2;
    config.board = malloc(sizeof(char *) * (config.board_size + 1));
    for (i = 0; map[i] != NULL; i++) {
        config.board[i] = strdup(map[i]);
        free(map[i]);
    }
    config.board[i] = NULL;
    free(map);
    free(board_buffer);
    return (config);
}