LIBFT_PATH	=	./Libft/
BUILT_PATH	=	./builtin/

OS := ${shell uname}

ifeq (${OS}, Linux)
    READLINE = /usr/include/readline/
else
    READLINE = /opt/homebrew/opt/readline/
endif

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
				./ft_lst_utils_serie.c \
				./signals/main_signals.c \
				./execve.c \
				./exec_redir.c \
				./exec_function.c \
				./free.c \
				./error.c \
				./ft_here_doc.c \

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