## Makefile for cherokee
##
## Made by BOURDALE Jules
## Login   <bourda_j@etna-alternance.net>
##
## Started on  Fri Jan 25 18:14:57 2017 BOURDALE Jules

CC 		= 	gcc

SRC 	= 	src/main.c \
			src/worker/worker.c \
			src/utils/process.c \
			src/utils/method.c \
			src/utils/strings.c \
			src/parser/parser.c \
			src/request/headers/headers.c \
			src/request/body.c \
			src/request/request.c \

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

re:			fclean all

.PHONY:		all clean fclean re
