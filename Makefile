# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clorin <clorin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/29 10:24:56 by clorin            #+#    #+#              #
#    Updated: 2021/06/29 10:35:07 by clorin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

SRCS	= srcs/main.c srcs/utils.c

CC	= clang

FLAGS	= -Wall -Werror -Wextra

HEADER	= -I includes/

LIBS	= -lpthread

OBJ	= $(SRCS:.c=.o)

all:	$(NAME)

.c.o :	
		@printf "\033[0;33mGenerating Philosopher's objects... %-33.33s\r" $@
		@$(CC) $(FLAGS) $(HEADER) -c $< -o $(<:.c=.o)

$(NAME): $(OBJ)
		@$(CC) $(FLAGS) $(HEADER) $(OBJ) -o $(NAME) $(LIBS)
		@echo "\nBuilding philo : \033[32mOK\033[0m"

clean:	
	@rm -rf $(OBJ)
	@echo "Delete OBJ files : \033[32mOK\033[0m"

fclean:	clean
	@rm -rf $(NAME)
	@echo "Delete philosopher : \033[32mOK\033[0m"

re:	fclean all

run:	$(NAME)
	./philo

.PHONY:	all clean fclean re
