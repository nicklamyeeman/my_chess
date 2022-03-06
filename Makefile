##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

SRC_DIR	=	./src/

SRC		=	$(SRC_DIR)/board.c			\
			$(SRC_DIR)/chess.c			\
			$(SRC_DIR)/config.c			\
			$(SRC_DIR)/explode.c		\
			$(SRC_DIR)/game.c			\
			$(SRC_DIR)/keys.c			\
			$(SRC_DIR)/menu.c			\
			$(SRC_DIR)/options.c		\
			$(SRC_DIR)/pieces.c			\
			$(SRC_DIR)/tools.c			\
			$(SRC_DIR)/pieces/pawn.c	\
			$(SRC_DIR)main.c

INC		=	-I ./include

CFLAGS	+=	$(INC) -W -Wall -Wextra -g

NCFLAGS =	-lncurses

OBJ		=	$(SRC:.c=.o)

NAME	=	my_chess

all:	$(OBJ)
	gcc -o $(NAME) $(OBJ) $(NCFLAGS)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re