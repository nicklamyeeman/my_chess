/*
** EPITECH PROJECT, 2022
** my_chess
** File description:
** chess
*/

#include "chess.h"

e_state game_print(config_t config, game_t game)
{
    if (game.state == CLEAR_MENU_STATE) {
        clear();
        refresh();
        print_menu(config);
        return (MENU_STATE);
    }
    if (game.state == CLEAR_GAME_STATE) {
        clear();
        refresh();
        print_board(config);
        print_pieces(config);
        return (GAME_STATE_W);
    }
    return game.state;
}

void game_loop()
{
    config_t config = init_config();
    game_t game = init_game();
    int k = 0;

    options();
    print_menu(config);
    while (k != 27) {
        k = wgetch(stdscr);
        if (k == KEY_MOUSE)
            manage_key_mouse(&config, &game);
        if (k == 32 && (game.state == GAME_STATE_W || game.state == GAME_STATE_B))
            game.state = CLEAR_MENU_STATE;
        game.state = game_print(config, game);
    }
    endwin();
}

int my_chess()
{
    game_loop();
    return 0;
}