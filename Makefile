SRC = ./main.c \
	  ./parsing.c \
	  ./errors.c \
	  ./pthread.c \
	  ./exec.c \
	  ./ft_atoi.c \
	  ./ft_strcmp.c

OBJ = $(SRC:.c=.o)

NAME = philo

HEADERS = ./

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

.c.o:
	gcc $(FLAGS) -I $(HEADERS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJ)
	gcc $(OBJ) $(FLAGS) -I $(HEADERS) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re