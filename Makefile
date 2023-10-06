LIBFT_PATH	=	./Libft/
PIPEX_PATH	=	./pipex/
BUILTIN_PATH=	./builtin/
READLINE	=	/usr/include/readline

SRC 		= 	./main.c \
				./parsing.c \
				./lexer.c \
				./lexer_plus.c \
				./ft_lst_utils_lex.c \
				./help_function.c \
				./parser.c \

OBJ		= ${SRC:.c=.o}

HEADER		= ./

CC 			= clang

RM 			= rm -f

CFLAGS 		= -Wall -Werror -Wextra -g

ifdef DEBUG
	CFLAGS += -fsanitize=address -g3
endif

NAME 		= minishell

all:		$(NAME)

.c.o:
			@$(CC) $(CFLAGS) -I $(HEADER) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJ)
			@${MAKE} -C ${LIBFT_PATH}
			@${MAKE} -C ${BUILTIN_PATH}
			@$(CC) $(CFLAGS) $(OBJ) ${LIBFT_PATH}libft.a ${BUILTIN_PATH}builtin.a -L ${READLINE} -lreadline -I $(HEADER) -o $(NAME)

debug:
	${MAKE} DEBUG=1

clean:
			@$(RM) $(OBJ)
			@${MAKE} clean -C ${LIBFT_PATH}
			@${MAKE} clean -C ${BUILTIN_PATH}

fclean: 	clean
			@$(RM) $(NAME) ${LIBFT_PATH}libft.a ${BUILTIN_PATH}builtin.a

re:			fclean all

.PHONY: 	all clean fclean re