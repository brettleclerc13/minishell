# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/17 20:15:35 by ehouot            #+#    #+#              #
#    Updated: 2023/11/14 11:02:13 by brettlecler      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC 		= ft_isalpha.c \
				ft_isdigit.c \
				ft_isalnum.c \
				ft_isascii.c \
				ft_isprint.c \
				ft_strlen.c \
				ft_memset.c \
				ft_bzero.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_strlcpy.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_toupper.c \
				ft_tolower.c \
				ft_strlcat.c \
				ft_strcmp.c \
				ft_strncmp.c \
				ft_strchr.c \
				ft_strrchr.c \
				ft_strnstr.c \
				ft_atoi.c \
				ft_strdup.c \
				ft_calloc.c \
				ft_putchar_fd.c \
				ft_putstr_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_strmapi.c \
				ft_striteri.c \
				ft_substr.c \
				ft_strjoin.c \
				ft_itoa.c \
				ft_strtrim.c \
				ft_split.c \
				

SRC_BONUS	= ft_lstnew.c \
				ft_lstadd_front.c \
				ft_lstsize.c \
				ft_lstlast.c \
				ft_lstadd_back.c \
				ft_lstdelone.c \
				ft_lstclear.c \
				ft_lstiter.c

SRC_ADD		= ft_split_bash.c \
				ft_error.c \
				ft_count_quote.c \
				strjoin_functions.c \
				ft_split_bash_error.c

OBJ 		= $(SRC:.c=.o)

OBJ_BONUS	= $(SRC_BONUS:.c=.o)

OBJ_ADD		= $(SRC_ADD:.c=.o)

CC 			= clang

RM 			= rm -f

CFLAGS 		= -Wall -Werror -Wextra

NAME 		= libft.a

all:		$(NAME)

.c.o:
			$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJ) $(OBJ_ADD)
			ar rcs $(NAME) $(OBJ) $(OBJ_ADD)

bonus:		$(OBJ) $(OBJ_BONUS) $(OBJ_ADD)
			ar rcs $(NAME) $(OBJ) $(OBJ_BONUS) $(OBJ_ADD)

clean:
			$(RM) $(OBJ) $(OBJ_BONUS) $(OBJ_ADD)

fclean: 	clean
			$(RM) $(NAME)

re:			fclean $(NAME)

.PHONY: 	all clean fclean re bonus