## Makefile for cherokee
##
## Made by BOURDALE Jules
## Login   <bourda_j@etna-alternance.net>
##
## Started on  Fri Jan 25 18:14:57 2017 BOURDALE Jules

CC 		= 	gcc

LDLIBS  =   -lpython3.6

CFLAGS  =   -Wall -Werror -g -I/usr/include/python3.6m -L/usr/include/python3.6m

PLIB:=$(shell /usr/bin/python3-config --ldflags) #--cflags

SRC 	= 	src/main.c \
			src/log/log.c \
			src/worker/worker.c \
			src/utils/process.c \
			src/utils/method.c \
			src/utils/strings.c \
			src/utils/file.c \
			src/utils/dir.c \
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
			src/response/content/html_static_dir.c \
			src/response/content/serve_custom_location.c \
			src/response/content/not_found.c \
			src/response/content/not_implemented.c \
			src/response/httpdd/httpdd.c \
			src/response/httpdd/is_static_file.c \
			src/response/httpdd/has_method_implemented.c \
			src/response/httpdd/is_static_directory.c \
			src/response/httpdd/is_static_location.c \
			src/response/httpdd/is_method.c \
			src/custom/custom.c \
			src/custom/call.c \

NAME	=	Cherokee

OBJ		=	$(SRC:.c=.o)

all: 		$(NAME)

$(NAME):	$(OBJ)
			$(CC) -o $(NAME) $(OBJ) -pthread $(LDFLAGS) $(PLIB)

clean:
			rm -f $(OBJ)

fclean:		clean
			rm -f ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
