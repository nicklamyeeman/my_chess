/*
** EPITECH PROJECT, 2022
** my_chess
** File description:
** pawn
*/

#include "chess.h"

char **check_pawn_atk(config_t config, game_t game, char **possibilities, int *i)
{
    char color = game.selected_piece[0];
    int y = config.board_size - atoi(game.selected_piece + 2);
    int x = (game.selected_piece[1] - 'A') * 2;
    int direction = (color == 'w') ? -1 : 1;

    if (x > 1 &&
        config.placement[y + direction][x - 2 + 1] != color &&
        config.placement[y + direction][x - 2] != '-')
        asprintf(&possibilities[(*i)++], "%d%d", y + direction, (x - 2) / 2);
    if (x < (config.board_size - 1) * 2 &&
        config.placement[y + direction][x + 2 + 1] != color &&
        config.placement[y + direction][x + 2] != '-')
        asprintf(&possibilities[(*i)++], "%d%d", y + direction, (x + 2) / 2);
    possibilities[*i] = NULL;
    return possibilities;
}

char **check_pawn_move(config_t config, game_t game)
{
    char **possibilities = NULL;
    char color = game.selected_piece[0];
    int y = config.board_size - atoi(game.selected_piece + 2);
    int x = (game.selected_piece[1] - 'A') * 2;
    int direction = (color == 'w') ? -1 : 1;
    int i = 0;

    possibilities = malloc(sizeof(char *) * 5);
    if (config.placement[y + direction][x] == '-')
        asprintf(&possibilities[i++], "%d%d", y + direction, x / 2);
    if ((color == 'w' && y == config.board_size - 2) || (color == 'b' && y == 1)) {
        if (config.placement[y+ direction][x] == '-' &&
            config.placement[y + direction * 2][x] == '-')
            asprintf(&possibilities[i++], "%d%d", y + direction * 2, x / 2);
    }
    return check_pawn_atk(config, game, possibilities, &i);
}

int pawn_move(config_t config, game_t game)
{
    char **possible_moves = check_pawn_move(config, game);
    int y = 0;
    int x = 0;

    if (possible_moves == NULL)
        return 1;
    attron(BLCK_ON_CYAN);
    for (int i = 0; possible_moves[i] != NULL; i++) {
        y = possible_moves[i][0] - '0';
        x = possible_moves[i][1] - '0';
        print_piece_at(y, x, config.placement[y][x * 2], config.placement[y][x * 2 + 1]);
    }
    for (int i = 0; possible_moves[i] != NULL; i++)
        free(possible_moves[i]);
    free(possible_moves);
    return 0;
}