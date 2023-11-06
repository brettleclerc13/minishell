LIBFT_PATH	=	./Libft/
PIPEX_PATH	=	./pipex42/
BUILT_PATH	=	./builtin/

READLINE	=	/opt/homebrew/opt/readline/

SRC_MAIN 	= 	./main.c \
				./parsing.c \
				./lexer.c \
				./lexer_plus.c \
				./ft_lst_utils_lex.c \
				./help_function.c \
				./parser.c \
				./ft_split_word.c \
				./array_manipulation.c \
				./var_manipulation.c \
				./init.c \
				./execute.c \
				./parser_dollar.c \
				./serie.c \
				./signals/main_signals.c \

SRC_BUILTIN	=	${addprefix ${BUILT_PATH}, ./builtin_main.c \
											./ft_cd.c \
											./envp.c \
											./ft_env.c \
											./ft_pwd.c \
											./ft_export.c \
											./print_export.c \
	  										./ft_echo.c \
											./ft_unset.c \
											./ft_exit.c}

SRC = ${SRC_MAIN} ${SRC_BUILTIN}

OBJ		= ${SRC:.c=.o}

HEADER		= ./headers

CC 			= clang

RM 			= rm -f

CFLAGS 		= -Wall -Werror -Wextra -g
LDFLAGS		= -L/usr/local/opt/readline/lib
CPPFLAGS	= -I/usr/local/opt/readline/include

ifdef DEBUG
	CFLAGS += -fsanitize=address -g3
endif

NAME 		= minishell

all:		$(NAME)

.c.o:
			@$(CC) $(CFLAGS) -I $(HEADER) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJ)
			@${MAKE} -C ${LIBFT_PATH}
			@$(CC) $(CFLAGS) $(OBJ) ${LIBFT_PATH}libft.a -L$(shell brew --prefix readline)/lib -lreadline -I $(HEADER) -o $(NAME)

debug:
	${MAKE} DEBUG=1

clean:
			@$(RM) $(OBJ)
			@${MAKE} clean -C ${LIBFT_PATH}

fclean: 	clean
			@$(RM) $(NAME) ${LIBFT_PATH}libft.a

re:			fclean all

.PHONY: 	all clean fclean re