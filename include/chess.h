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

#define ROCK    "./ressources/pieces/rock.txt"
#define PAWN    "./ressources/pieces/pawn.txt"
#define KNIGHT  "./ressources/pieces/knight.txt"
#define BISHOP  "./ressources/pieces/bishop.txt"
#define KING    "./ressources/pieces/king.txt"
#define QUEEN   "./ressources/pieces/queen.txt"

#define YLLW_ON_BLCK COLOR_PAIR(1)
#define BLCK_ON_YLLW COLOR_PAIR(2)

typedef enum
{
    CLEAR_MENU_STATE,
    MENU_STATE,
    CLEAR_GAME_STATE,
    GAME_STATE
} e_state;

typedef enum
{
    DEFAULT_CONFIG,
    CUSTOM_CONFIG
} e_config;

typedef struct s_menu
{
    int y0, x0;
    int y1, x1;
    int y2, x2;
    int y_default;
    int y_custom;
    int y_play;
} menu_t;

typedef struct s_config
{
    e_config state;
    int player;
    int board_size;
    char **placement;

    menu_t yx_menu;
} config_t;

/* board */



/* chess */

    /**
     * @brief print in the terminal regarding the state and chenge it back to now print in loop
     * 
     * @param {config_t} config - config struct where menu usefull pos are stock 
     * @param {e_state} state - state of the current window 
     * @return {e_state} the new state if changed or current if not 
     */
    e_state game_print(config_t config, e_state state);

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

/* keys */

    /**
     * @brief check if click on the number of players in menu state
     * 
     * @param {e_state} state - state that can be modified if clicked 
     * @param {config_t} config - the config struct where are stocked every usefull menu coords 
     * @param {int} y - event click mouse position in y axis
     * @param {int} x - event click mouse position in x axis 
     */
    void check_player(e_state *state, config_t *config, int y, int x);

        /**
     * @brief check if click on the placement configuration in menu state
     * 
     * @param {e_state} state - state that can be modified if clicked 
     * @param {config_t} config - the config struct where are stocked every usefull menu coords 
     * @param {int} y - event click mouse position in y axis
     */
    void check_placement(e_state *state, config_t *config, int y);

    /**
     * @brief check if click on the play button in menu state
     * 
     * @param {e_state} state - state that can be modified if clicked 
     * @param {config_t} config - the config struct where are stocked every usefull menu coords 
     * @param {int} y - event click mouse position in y axis
     */
    void check_play(e_state *state, config_t *config, int y);

    /**
     * @brief manage the event of the mouse and check where is clicked
     * 
     * @param {config *} config - adress of the config to update the config
     * @param {e_state} state - where are we in the game ?  
     * @return {e_state} where will we be in the game 
     */
    e_state manage_key_mouse(config_t *config, e_state state);

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

/* tools */

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

#endif /* !CHESS_H_ */
