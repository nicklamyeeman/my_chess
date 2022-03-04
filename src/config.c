/*
** EPITECH PROJECT, 2022
** my_chess
** File description:
** config
*/

#include "chess.h"

config_t init_config(void)
{
    char *menu_buffer = open_read_file(MENU);
    char **menu = explode(menu_buffer, '\n');
    char **map = malloc(sizeof(char *) * 8);
    
    map[0] = strdup("RbNbBbKbQbBbNbRb");
    map[1] = strdup("PbPbPbPbPbPbPbPb");
    map[2] = strdup("----------------");
    map[3] = strdup("----------------");
    map[4] = strdup("----------------");
    map[5] = strdup("----------------");
    map[6] = strdup("PwPwPwPwPwPwPwPw");
    map[7] = strdup("RwNwBwKwQwBwNwRw");
    config_t config = update_config(DEFAULT_CONFIG, 2, 8, map);
    config.yx_menu = get_yx_menu(menu);
    return (config);
}

config_t update_config(e_config state, int player, int board_size, char **map)
{
    config_t config;

    config.state = state;
    config.player = player;
    config.board_size = board_size;
    config.placement = malloc(sizeof(char *) * (config.board_size + 1));
    for (int i = 0; i != config.board_size; i++)
        config.placement[i] = strdup(map[i]);
    return (config);
}

void free_config(config_t config)
{
    for (int i = 0; i != config.board_size; i++)
        free(config.placement[i]);
    free(config.placement);
}