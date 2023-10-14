# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/31 09:35:20 by ehouot            #+#    #+#              #
#    Updated: 2023/10/14 11:51:21 by ehouot           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT_PATH	=	./Libft

GNL_PATH	= 	./Get_next_line/

SRC 		= 	./main.c \
				./parsing.c \
				./exec_cmd.c \
				
SRC_BONUS	=	./main_bonus.c \
				./parsing_bonus.c \
				./exec_cmd_bonus.c \
				./ft_mandatory.c \
				./ft_close.c \

SRC_GNL		=	 $(addprefix $(GNL_PATH), get_next_line.c \
				get_next_line_utils.c)

OBJS		= ${SRC:.c=.o}
OBJS_BONUS	= ${SRC_BONUS:.c=.o} ${SRC_GNL:.c=.o}

ifndef BONUS
OBJ 		= ${OBJS}
else
OBJ			= ${OBJS_BONUS}
endif

HEADER		= ./

CC 			= clang

RM 			= rm -f

CFLAGS 		= -Wall -Werror -Wextra -g

ifdef DEBUG
	CFLAGS += -fsanitize=address -g3
endif

NAME 		= pipex

all:		$(NAME)

.c.o:
			@$(CC) $(CFLAGS) -I $(HEADER) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJ)
			@${MAKE} -C ${LIBFT_PATH}
			@$(CC) $(CFLAGS) $(OBJ) ${LIBFT_PATH}libft.a -I $(HEADER) -o $(NAME)

bonus:
	@${MAKE}	BONUS=1

debug:
	${MAKE} DEBUG=1

clean:
			@$(RM) $(OBJS) $(OBJS_BONUS)
			@${MAKE} clean -C ${LIBFT_PATH}

fclean: 	clean
			@$(RM) $(NAME) ${LIBFT_PATH}libft.a

re:			fclean all

.PHONY: 	all clean fclean re bonus