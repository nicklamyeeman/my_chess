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
#include <stdbool.h>
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
    INIT_GAME_STATE,
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

typedef struct s_piece
{
    int y;
    int x;
    char piece;
    char color;
    char **ressource;
    char **possible_moves;
    void (*p_highlight)(void *);
    void (* p_move)(void *, int, int);
} piece_t;

typedef struct s_game
{
    e_turn turn;
    piece_t *pieces;
    piece_t selected_piece;
    char **history;
} game_t;

typedef struct s_menu
{
    int y0, x0;
    int y1, x1;
    int y2, x2;
    int y_default;
    int y_custom;
    int y_play;
    char **menu;
} menu_t;

typedef struct s_config
{
    e_config config;
    int nb_player;
    int board_size;
    int case_size[2];
    char **board_ressource;
    char **board;
} config_t;

typedef struct s_chess
{
    e_state state;
    config_t config;
    menu_t menu;
    game_t game;
} chess_t;

/* board */

    /**
     * @brief print a board case at a coord
     * 
     * @param {config_t} config - config where is the board 
     * @param {int} y - line 
     * @param {int} x - col
     */
    void print_board_at(config_t config, int y, int x);

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
     * @param {chess_t} chess - chess struct where are state, menu, config and game struct 
     * @return {e_state} the new state if changed or current if not 
     */
    e_state game_print(chess_t chess);

    /**
     * @brief loop of the main game
     * 
     * @param {chess_t} chess - object chess containing everything
     */
    void chess_loop(chess_t chess);

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
     * @param {e_config} econfig - state of the config (default or custom)
     * @param {int} nb_player - number of players (default 2)
     * @param {int} board_size - size of the board (default 8) 
     * @param {char **} map - placement of pieces on the board 
     * @return {config_t} the new config
     */
    config_t update_config(e_config econfig, int nb_player, int board_size, char **map);

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
     * @brief clear highlight of the seleted piece
     * 
     * @param (config_t} config - config for board ressource
     * @param (game_t *} game - selected piece
     */
    void clear_highlight(config_t config, game_t *game);

    /**
     * @brief highilight selected pieces and possibility of move
     * 
     * @param {chess_t *} chess - chess struct with config and game  
     * @return {e_turn} which color turn will it be  
     */
    e_turn highlight_piece(chess_t *chess);

    /**
     * @brief move piece to toward click
     * 
     * @param {chess_t *} chess - chess struct
     * @param {int} normalize_y - y click
     * @param {int} normalize_x - x click 
     * @return e_turn 
     */
    e_turn move_piece(chess_t *chess, int normalize_y, int normalize_x);


/* keys */

    /**
     * @brief check if click on the number of players in menu state
     * 
     * @param {chess_t *} chess - chess struct with game and config   
     * @param {int} y - event click mouse position in y axis
     * @param {int} x - event click mouse position in x axis 
     */
    void check_menu_player(chess_t *chess, int y, int x);

        /**
     * @brief check if click on the placement configuration in menu state
     * 
     * @param {chess_t *} chess - chess struct with game and config   
     * @param {int} y - event click mouse position in y axis
     */
    void check_menu_placement(chess_t *chess, int y);

    /**
     * @brief check if click on the play button in menu state
     * 
     * @param {chess_t *} chess - chess struct with game and config   
     * @param {int} y - event click mouse position in y axis
     */
    void check_menu_play(chess_t *chess, int y);

    /**
     * @brief check where the click is
     * 
     * @param {chess_t *} chess - chess struct with game and config   
     * @param {MEVENT} event - mouse event containing the mouse position
     * @param {char} color - color of the player's turn (white or black)
     * @return {e_state} new state of the game (turn off or not) 
     */
    void check_game_case(chess_t *chess, MEVENT event, char color);

    /**
     * @brief manage the event of the mouse and check where is clicked
     * 
     * @param {chess_t *} chess - chess struct with game and config   
     */
    void manage_key_mouse(chess_t *chess);

/* menu */

    /**
     * @brief Get the usefull xy of the menu 
     * 
     * @param {menu_t} menu - the menu contining the menu map
     * @return {menu_t} the struct containing all the usefull xy of the menu  
     */
    menu_t get_yx_menu(menu_t yx_menu);

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
     * @param {menu_t} menu - menu usefull informations
     * @param {config_t} config - config for highlight in menu 
     */
    void print_menu(menu_t menu, config_t config);

    /**
     * @brief initialize the menu
     * 
     * @return {menu_t} the menu struct with position of different sections
     */
    menu_t init_menu(void);

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
     * @brief Get the piece at yx position
     * 
     * @param {piece_t *} pieces - tab of pieces in the game
     * @param {int} x - looking for that x 
     * @return piece_t 
     */
    piece_t get_piece_at(piece_t *pieces, int y, int x);

    /**
     * @brief 
     * 
     * @param chess 
     * @param old_y 
     * @param old_x 
     */
    void update_pieces_from_selected(chess_t *chess, int old_y, int old_x);

    /**
     * @brief print a piece
     * 
     * @param {piece_t} piece - piece informations
     */
    void print_piece(piece_t piece);

    /**
     * @brief print all pieces in the board
     * 
     * @param {game_t} game - game structwhere are stocked pieces placement
     */
    void print_pieces(game_t game);

    /**
     * @brief number of pieces available in the game
     * 
     * @param {char *} pieces - string with all pieces "PRNBKQ" by default 
     * @param {config_t} config - config where there is the map 
     * @return {int} the number of pieces in the map
     */
    int nb_pieces(char *pieces, config_t config);

    /**
     * @brief Set the pieces object in the chess game struct
     * 
     * @param {config_t} config - config where is set the board disposition 
     * @param {game_t} game - game struct with usefull informations for game
     * @return {game_t} the setup game struct with pieces 
     */
    game_t set_pieces(config_t config, game_t game);

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
     * @brief check all possibility of the pawn special move and return the possibilities
     * 
     * @param {config_t} config - config struct where are the board size and the board 
     * @param {game_t} game - game struct where is the selected piece 
     * @param {char **} possibilities - array of possibilities being fill 
     * @param {int} i - the position of actual array to fill 
     * @return {char **} array of the different possibilities 
     */
    char **check_pawn_spc(config_t config, game_t game, char **possibilities, int *i);

    /**
     * @brief check all possibility of the pawn attack move and return the possibilities
     * 
     * @param {chess_t *} chess - chess struct where is the history and selected piece 
     * @param {char **} possibilities - array of possibilities being fill 
     * @param {int} i - the position of actual array to fill 
     * @return {char **} array of the different possibilities 
     */
    char **check_pawn_atk(piece_t piece, config_t config, char **possibilities, int *i);

    /**
     * @brief check all possibility of the pawn move and return the possibilities
     * @param {piece_t} piece - piece to cehck move
     * @param {config_t} config - config to check the board configuration
     * @return {char **} array of the different possibilities 
     */
    char **check_pawn_move(piece_t piece, config_t config);
    
    /**
     * @brief check move of the pawn and 
     * 
     * @param {chess_t *} chess - chess struct where is the history and selected piece 
     */
    void pawn_highlight(chess_t *chess);

    /**
     * @brief check move of the pawn and 
     * 
     * @param {chess_t *} chess - chess struct where is the history and selected piece 
     */
    void pawn_move(chess_t *chess, int y, int x);

/* pieces/knight */

    /**
     * @brief check all possibility of the knight move and return the possibilities
     * @param {piece_t} piece - piece to cehck move
     * @param {config_t} config - config to check the board configuration
     * @return {char **} array of the different possibilities 
     */
    char **check_knight_move(piece_t piece, config_t config);
    
    /**
     * @brief check move of the knight and 
     * 
     * @param {chess_t *} chess - chess struct where is the history and selected piece 
     */
    void knight_highlight(chess_t *chess);

    /**
     * @brief check move of the knight and 
     * 
     * @param {chess_t *} chess - chess struct where is the history and selected piece 
     */
    void knight_move(chess_t *chess, int y, int x);

/* pieces/king */

    /**
     * @brief check all possibility of the king move and return the possibilities
     * @param {piece_t} piece - piece to cehck move
     * @param {config_t} config - config to check the board configuration
     * @return {char **} array of the different possibilities 
     */
    char **check_king_move(piece_t piece, config_t config);
    
    /**
     * @brief check move of the king and 
     * 
     * @param {chess_t *} chess - chess struct where is the history and selected piece 
     */
    void king_highlight(chess_t *chess);

    /**
     * @brief check move of the king and 
     * 
     * @param {chess_t *} chess - chess struct where is the history and selected piece 
     */
    void king_move(chess_t *chess, int y, int x);

/* pieces/bishop */

    /**
     * @brief check all possibility of the bishop move and return the possibilities
     * @param {piece_t} piece - piece to cehck move
     * @param {config_t} config - config to check the board configuration
     * @return {char **} array of the different possibilities 
     */
    char **check_bishop_move(piece_t piece, config_t config);
    
    /**
     * @brief check move of the bishop and 
     * 
     * @param {chess_t *} chess - chess struct where is the history and selected piece 
     */
    void bishop_highlight(chess_t *chess);

    /**
     * @brief check move of the bishop and 
     * 
     * @param {chess_t *} chess - chess struct where is the history and selected piece 
     */
    void bishop_move(chess_t *chess, int y, int x);

/* pieces/rock */

    /**
     * @brief check all possibility of the rock move and return the possibilities
     * @param {piece_t} piece - piece to cehck move
     * @param {config_t} config - config to check the board configuration
     * @return {char **} array of the different possibilities 
     */
    char **check_rock_move(piece_t piece, config_t config);
    
    /**
     * @brief check move of the rock and 
     * 
     * @param {chess_t *} chess - chess struct where is the history and selected piece 
     */
    void rock_highlight(chess_t *chess);

    /**
     * @brief check move of the rock and 
     * 
     * @param {chess_t *} chess - chess struct where is the history and selected piece 
     */
    void rock_move(chess_t *chess, int y, int x);

/* pieces/queen */

    /**
     * @brief check all possibility of the queen move and return the possibilities
     * @param {piece_t} piece - piece to cehck move
     * @param {config_t} config - config to check the board configuration
     * @return {char **} array of the different possibilities 
     */
    char **check_queen_move(piece_t piece, config_t config);
    
    /**
     * @brief check move of the queen and 
     * 
     * @param {chess_t *} chess - chess struct where is the history and selected piece 
     */
    void queen_highlight(chess_t *chess);

    /**
     * @brief check move of the queen and 
     * 
     * @param {chess_t *} chess - chess struct where is the history and selected piece 
     */
    void queen_move(chess_t *chess, int y, int x);

#endif /* !CHESS_H_ */
