##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

SRC_DIR	=	./src

SRC		=	$(SRC_DIR)/c_board.c			\
			$(SRC_DIR)/c_chess.c			\
			$(SRC_DIR)/c_config.c			\
			$(SRC_DIR)/explode.c			\
			$(SRC_DIR)/c_game.c				\
			$(SRC_DIR)/c_keys.c				\
			$(SRC_DIR)/c_menu.c				\
			$(SRC_DIR)/c_options.c			\
			$(SRC_DIR)/c_pieces.c			\
			$(SRC_DIR)/c_tools.c			\
			$(SRC_DIR)/pieces/c_pawn.c		\
			main.c

INC		=	-I ./include

CFLAGS	+=	$(INC) -W -Wall -Wextra -g

NCFLAGS =	-lncurses

MEMLEAK	=	-fsanitize=address

OBJ		=	$(SRC:.c=.o)

NAME	=	my_chess

all:	$(OBJ)
	gcc -o $(NAME) $(OBJ) $(NCFLAGS)

memory-leak: $(OBJ)
	gcc -o $(NAME) $(OBJ) $(MEMLEAK) $(NCFLAGS)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re