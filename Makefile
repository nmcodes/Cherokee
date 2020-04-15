## Makefile for cherokee
##
## Made by BOURDALE Jules
## Login   <bourda_j@etna-alternance.net>
##
## Started on  Fri Jan 25 18:14:57 2017 BOURDALE Jules

CC 		= 	gcc

SRC 	= 	src/main.c \
			src/log/log.c \
			src/worker/worker.c \
			src/utils/process.c \
			src/utils/method.c \
			src/utils/strings.c \
			src/utils/file.c \
			src/parser/parser.c \
			src/headers/headers.c \
			src/headers/content_length.c \
			src/headers/content_type.c \
			src/headers/date.c \
			src/headers/server.c \
			src/request/body.c \
			src/request/request.c \
			src/config/config.c \
			src/inih/ini.c \
			src/threadpool/thpool.c \
			src/response/response.c \
			src/response/content/serve_static_file.c \
			src/response/content/not_found.c \
			src/response/httpdd/httpdd.c \
			src/response/httpdd/is_static_file.c \
			src/response/httpdd/is_static_directory.c \
			src/response/httpdd/is_static_location.c \
			src/response/httpdd/is_get_method.c \

NAME	=	Cherokee

OBJ		=	$(SRC:.c=.o)

CFLAGS	+=	-W -Wall -Werror -g3

LDFLAGS	=

all: 		$(NAME)

$(NAME):	$(OBJ)
			$(CC) -o $(NAME) $(OBJ) -pthread $(LDFLAGS)

clean:
			rm -f $(OBJ)

fclean:		clean
			rm -f ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
