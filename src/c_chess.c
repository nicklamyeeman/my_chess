/*
** EPITECH PROJECT, 2022
** my_chess
** File description:
** chess
*/

#include "c_chess.h"

e_state game_state(chess_t *chess)
{
    if (chess->state == CLEAR_MENU_STATE) {
        clear();
        refresh();
        print_menu(chess->menu, chess->config);
        return (MENU_STATE);
    }
    if (chess->state == INIT_GAME_STATE) {
        chess->game = set_pieces(chess->config, chess->game);
        chess->state = CLEAR_GAME_STATE;
    }
    if (chess->state == CLEAR_GAME_STATE) {
        clear();
        refresh();
        print_board(chess->config);
        for (int k = 0; chess->game.pieces[k].ressource != NULL; k++)
            print_piece(chess->game.pieces[k]);
        return (GAME_STATE_W);
    }
    if (chess->state == GAME_STATE_W && chess->game.turn == NEXT_TURN) {
        // if (chess->game.king_threat.ressource != NULL) {
        //     attron(BLCK_ON_RED);
        //     print_piece(find_piece(chess->game.pieces, 'K', 'b'));
        // }
        chess->state = GAME_STATE_B;
        chess->game.turn = SELECT_PIECE;
    }
    if (chess->state == GAME_STATE_B && chess->game.turn == NEXT_TURN) {
        // if (chess->game.king_threat.ressource != NULL) {
        //     attron(BLCK_ON_RED);
        //     print_piece(find_piece(chess->game.pieces, 'K', 'w'));
        // }
        chess->state = GAME_STATE_W;
        chess->game.turn = SELECT_PIECE;
    }
    return chess->state;
}

void chess_loop(chess_t chess)
{
    int k = 0;

    options();
    print_menu(chess.menu, chess.config);
    while (k != 27) {
        k = wgetch(stdscr);
        if (k == KEY_MOUSE)
            manage_key_mouse(&chess);
        if (k == 32 && (chess.state == GAME_STATE_W || chess.state == GAME_STATE_B))
            chess.state = CLEAR_MENU_STATE;
        chess.state = game_state(&chess);
        if (chess.config.board != NULL) {
            for (int i = 0; chess.config.board[i] != NULL; i++)
                mvprintw(i + (chess.config.board_size * chess.config.case_size[0]) / 2 - chess.config.board_size / 2, chess.config.board_size * chess.config.case_size[1] + chess.config.board_size / 2, "%s", chess.config.board[i]);
        }
    }
    endwin();
}

int my_chess()
{
    chess_t chess;

    chess.config = init_config();
    chess.menu = init_menu();
    chess.game = init_game();
    chess.state = MENU_STATE;
    chess_loop(chess);
    return 0;
}