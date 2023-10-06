LIBFT_PATH =../Libft/

SRC =		./main.c \
	  		./ft_cd.c \
			./envp.c \
			./ft_pwd.c \
	  		./ft_echo.c

OBJ =		$(SRC:.c=.o)

NAME =		builtin

HEADERS =	./

FLAGS =		-Wall -Wextra -Werror

all:		$(NAME)

.c.o:
			gcc $(FLAGS) -I $(HEADERS) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJ)
			@${MAKE} -C ${LIBFT_PATH}
			gcc $(OBJ) $(FLAGS) ${LIBFT_PATH}libft.a -I $(HEADERS) -o $(NAME)

clean:
			rm -f $(OBJ)
			@${MAKE} clean -C ${LIBFT_PATH}

fclean:		clean
			rm -f $(NAME)
			@$(RM) $(NAME) ${LIBFT_PATH}libft.a

re:			fclean all

.PHONY:		all clean fclean re
