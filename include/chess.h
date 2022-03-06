/*
** EPITECH PROJECT, 2022
** chess
** File description:
** chess
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <ncurses.h>

#ifndef CHESS_H_
#define CHESS_H_

#define MENU    "./ressources/menu.txt"
#define BOARD   "./ressources/board.txt"

#define ROCK    "./ressources/pieces/rock.txt"
#define PAWN    "./ressources/pieces/pawn.txt"
#define KNIGHT  "./ressources/pieces/knight.txt"
#define BISHOP  "./ressources/pieces/bishop.txt"
#define KING    "./ressources/pieces/king.txt"
#define QUEEN   "./ressources/pieces/queen.txt"

#define YLLW_ON_BLCK COLOR_PAIR(1)
#define BLCK_ON_YLLW COLOR_PAIR(2)
#define BLCK_ON_CYAN COLOR_PAIR(3)
#define BLCK_ON_MGNT COLOR_PAIR(4)

typedef enum
{
    CLEAR_MENU_STATE,
    MENU_STATE,
    CLEAR_GAME_STATE,
    GAME_STATE_W,
    GAME_STATE_B
} e_state;

typedef enum
{
    DEFAULT_CONFIG,
    CUSTOM_CONFIG
} e_config;

typedef enum
{
    SELECT_PIECE,
    SELECT_DEST,
    NEXT_TURN
} e_turn;

typedef struct s_menu
{
    int y0, x0;
    int y1, x1;
    int y2, x2;
    int y_default;
    int y_custom;
    int y_play;
} menu_t;

typedef struct s_game
{
    e_state state;
    e_turn turn;
    char **history;
    char *selected_piece;
} game_t;

typedef struct s_config
{
    e_config state;
    int player;
    int board_size;
    int y_case_size;
    int x_case_size;
    char **placement;

    menu_t yx_menu;
} config_t;

/* board */

    /**
     * @brief free the board after printed
     * 
     * @param {char *} board_buffer - buffer read from file of the board 
     * @param {char **} board - array where the board is stocked 
     */
    void free_board(char *board_buffer, char **board);

    /**
     * @brief print the board 
     * 
     * @param {config_t} config - config struct where is stocked usefull information like size and pieces placement 
     */
    void print_board(config_t config);

/* chess */

    /**
     * @brief print in the terminal regarding the state and chenge it back to now print in loop
     * 
     * @param {config_t} config - config struct where menu usefull pos are stock 
     * @param {game_t} game - game struct containing the state of the game 
     * @return {e_state} the new state if changed or current if not 
     */
    e_state game_print(config_t config, game_t game);

    /**
     * @brief loop of the main game
     * 
     */
    void game_loop();

    /**
     * @brief main loop
     * 
     * @return {int} return value of the binary
     */
    int my_chess();

/* config */

    /**
     * @brief initialize the config struct
     * 
     * @return {config_t} the initialized config with default value
     */
    config_t init_config(void);

    /**
     * @brief update the default / previous config with the new one passed as arguments
     * 
     * @param {e_config} state - state of the config (default or custom)
     * @param {int} player - number of players (default 2)
     * @param {int} board_size - size of the board (default 8) 
     * @param {char **} map - placement of pieces on the board 
     * @return {config_t} the new config
     */
    config_t update_config(e_config state, int player, int board_size, char **map);

    /**
     * @brief free the config struct
     * 
     * @param {config_t} config - the config to free 
     */
    void free_config(config_t config);

/* explode */

    /**
     * @brief count the number of line of the future array
     * 
     * @param {char *} str - string to explode 
     * @param {char} separator - separator for the future array 
     * @return {int} number of line of the future array 
     */
    int nb_line(char *str, char separator);

    /**
     * @brief malloc the array for explode 
     * 
     * @param {char *} str - string to explode 
     * @param {char} separator - separator for the future array 
     * @return {char**} the array malloc'ed
     */
    char **malloc_array(char *str, char separator);
    
    /**
     * @brief transform string to array with separator
     * 
     * @param {char *} str - string to explode
     * @param {char} separator - separator for the future array
     * @return {char **} the array exploded
     */
    char **explode(char *str, char separator);

/* game */

    /**
     * @brief init gmae struct for the game
     * 
     * @return {game_t} the initialized struct 
     */
    game_t init_game(void);

    /**
     * @brief highilight selected pieces and possibility of move
     * 
     * @param {config_t} config - config struct containing usefull informations  
     * @param {game_t} game - game struct containing the game options and history mainly 
     * @param {int} normalize_y - position of clicked piece in line / y axis 
     * @param {int} normalize_x - position of clicked piece in column / x axis 
     * @return {e_turn} which color turn will it be  
     */
    e_turn highlight_piece(config_t config, game_t *game, int normalize_y, int normalize_x);

/* keys */

    /**
     * @brief check if click on the number of players in menu state
     * 
     * @param {config_t *} config - the config struct where are stocked every usefull menu coords 
     * @param {game_t *} game - the game struct containing the state 
     * @param {int} y - event click mouse position in y axis
     * @param {int} x - event click mouse position in x axis 
     */
    void check_menu_player(config_t *config, game_t *game, int y, int x);

        /**
     * @brief check if click on the placement configuration in menu state
     * 
     * @param {config_t *} config - the config struct where are stocked every usefull menu coords 
     * @param {game_t *} game - the game struct containing the state 
     * @param {int} y - event click mouse position in y axis
     */
    void check_menu_placement(config_t *config, game_t *game, int y);

    /**
     * @brief check if click on the play button in menu state
     * 
     * @param {config_t *} config - the config struct where are stocked every usefull menu coords 
     * @param {game_t *} game - the game struct containing the state 
     * @param {int} y - event click mouse position in y axis
     */
    void check_menu_play(config_t *config, game_t *game, int y);

    /**
     * @brief check where the click is
     * 
     * @param {config_t *} config - game config struct where are stocked usefull informations 
     * @param {game_t *} game - the game struct
     * @param {MEVENT} event - mouse event containing the mouse position
     * @param {char} color - color of the player's turn (white or black)
     * @return {e_state} new state of the game (turn off or not) 
     */
    void check_game_case(config_t *config, game_t *game, MEVENT event, char color);

    /**
     * @brief manage the event of the mouse and check where is clicked
     * 
     * @param {config *} config - adress of the config to update the config
     * @param {game_t *} game - game struct   
     */
    void manage_key_mouse(config_t *config, game_t *game);

/* menu */

    /**
     * @brief Get the usefull xy of the menu 
     * 
     * @param {char **} menu - the menu  
     * @return {menu_t} the struct containing all the usefull xy of the menu  
     */
    menu_t get_yx_menu(char **menu);

    /**
     * @brief change color of the menu regarding the configs
     * 
     * @param {char **} menu - menu map that is displayed
     * @param {int} i - y axis (lines) 
     * @param {int} j - x axis (col) 
     * @param {config_t} config - the config chosen for the menu
     */
    void menu_config(char **menu, int i, int j, config_t config);

    /**
     * @brief free the menu loaded
     * 
     * @param {char *} menu_buffer - menu buffer read from file
     * @param {char **} menu - array where the menu is stocked 
     */
    void free_menu(char *menu_buffer, char **menu);

    /**
     * @brief print the menu of the game
     * 
     * @param {config_t} config - the config selected in the menu
     */
    void print_menu(config_t config);

/* options */

    /**
     * @brief options for ncurses window
     * 
     */
    void options(void);

    /**
     * @brief set up color pairs
     * 
     */
    void color_options(void);

/* pieces */

    /**
     * @brief free the pice buffer and array
     * 
     * @param {char *} piece_buffer - buffer ocntaining the piece asset
     * @param {char **} piece - array of the piece 
     */
    void free_piece(char *piece_buffer, char **piece);

    /**
     * @brief load, print and then free the piece to draw
     * 
     * @param {char *} assetpath - path to the ressource asset 
     * @param {int} i - y axis where to draw 
     * @param {int} j - x axis where to draw 
     * @param {char} color - b or w to chose the color 
     */
    void load_print_piece(char *assetpath, int i, int j, char color);

    /**
     * @brief print all pieces in the board
     * 
     * @param {config_t} config - config file where are stocked pices placement
     */
    void print_pieces(config_t config);

    /**
     * @brief print a piece at the position sent
     * 
     * @param {int} y - line to start to print 
     * @param {int} x - col to start to print
     * @param {char} color - color 'w' or 'b' 
     * @param {char} piece - piece to draw 
     */
    void print_piece_at(int y, int x, char color, char piece);

/* tools */

    /**
     * @brief free ressource loaded previously
     * 
     * @param {char *} buffer - buffer read from file
     * @param {char **} exploded - exploded buffer 
     */
    void free_ressource(char *buffer, char **exploded);

    /**
     * @brief calculate the number of line of an array
     * 
     * @param {char **} array - array to get the size 
     * @return {int} array size 
     */
    int array_len(char **array);

    /**
     * @brief prompt usage of binary
     * 
     * @param {int} return_value - value to return the binary
     * @return {int} return the value passed as argument
     */
    int usage(int return_value);

    /**
     * @brief Open, Read and Return a file content
     * 
     * @param {char *} filepath - path to the file to open
     * @return {char *} contains the content of the file
     */
    char *open_read_file(char *filepath);

/* pieces/pawn */

    /**
     * @brief check move of the pawn and 
     * 
     * @param {config_t} config - config struct where is the board 
     * @param {game_t *} game - game struct where is the history and selected piece 
     * @return {int} is the piece blocked ? 
     */
    int pawn_move(config_t config, game_t game);

#endif /* !CHESS_H_ */
