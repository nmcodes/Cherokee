## Makefile for cherokee
##
## Made by BOURDALE Jules
## Login   <bourda_j@etna-alternance.net>
##
## Started on  Fri Jan 25 18:14:57 2017 BOURDALE Jules

CC 		= 	gcc

SRC 	= 	$(wildcard src/*.c)

NAME	=	Cherokee

OBJ		=	$(SRC:.c=.o)

CFLAGS	+=	-W -Wall -Werror

LDFLAGS	=

all: 		$(NAME)

$(NAME):	$(OBJ)
			$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
			rm -f $(OBJ)

fclean:		clean
			rm -f ${NAME}

test:		$(TEST_OBJ)
			$(CC) $(LDFLAGS) -o $(NAME)_test $(TEST_OBJ)

re:			fclean all

.PHONY:		all clean fclean re
