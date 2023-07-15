# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/01 11:07:34 by yuboktae          #+#    #+#              #
#    Updated: 2023/07/15 13:39:17 by yuboktae         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

SRC_DIR	=	src/
OBJ_DIR	=	obj/
INC_DIR =	includes/

SRC_FILES	=	main.c \
				init.c \
				free.c \
				routine.c \
				philo.c \
				lib.c \
				utils.c \
							

SRC			=	$(addprefix $(SRC_DIR), $(SRC_FILES))
INC			=	-I $(INC_DIR)
OBJ			=	$(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))
DEP			=	$(OBJ:.o=.d)

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g3

all:	$(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -MMD -MP -o $@ -c $<
	
-include $(DEP)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re