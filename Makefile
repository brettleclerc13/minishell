LIBFT_PATH	=	./Libft/
BUILT_PATH	=	./builtin/
SIG_PATH	=	./signals/

OS := ${shell uname}

ifeq (${OS}, Linux)
    READLINE = /usr/include/readline/
else
    READLINE = /opt/homebrew/opt/readline/
endif

SRC_MAIN 	= 	./main.c \
				./parsing.c \
				./lexer.c \
				./ft_lst_utils_lex.c \
				./help_function.c \
				./parser.c \
				./ft_split_word.c \
				./ft_split_string.c \
				./array_manipulation.c \
				./var_manipulation.c \
				./init.c \
				./execute.c \
				./parser_dollar.c \
				./parser_d_lst.c \
				./serie.c \
				./ft_lst_utils_serie.c \
				./execve.c \
				./exec_redir.c \
				./in_out_redir.c \
				./exec_function.c \
				./free.c \
				./error.c \
				./ft_here_doc.c \
				./ft_lst_utils_dollar.c \
				./ft_count_redir.c

SRC_BUILTIN	=	${addprefix ${BUILT_PATH},	./builtin_main.c \
											./ft_cd.c \
											./ft_cd_manipulation.c \
											./envp.c \
											./ft_env.c \
											./ft_pwd.c \
											./ft_export.c \
											./print_export.c \
	  										./ft_echo.c \
											./ft_unset.c \
											./ft_exit.c}

SRC_SIGNALS	=	${addprefix ${SIG_PATH},	./heredoc_signals.c \
											./output_results.c \
											./ignore_signals.c \
											./in_command_signals.c \
											./main_signals.c}

SRC = ${SRC_MAIN} ${SRC_BUILTIN} ${SRC_SIGNALS}

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