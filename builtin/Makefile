SRC =		./main.c \
	  		./ft_cd.c \
			./envp.c \
			./ft_pwd.c \
			./ft_export.c \
	  		./ft_echo.c

OBJ =		$(SRC:.c=.o)

NAME =		builtin.a

HEADERS =	./

FLAGS =		-Wall -Wextra -Werror

all:		$(NAME)

.c.o:
			gcc $(FLAGS) -I $(HEADERS) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJ)
			ar rcs $(NAME) $(OBJ)

clean:
			rm -f $(OBJ)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
