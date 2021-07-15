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

NAME		= philo

BONUS		= philo_bonus

SRCS		= srcs/main.c srcs/utils.c srcs/routine.c srcs/timer.c srcs/printer.c \
			srcs/death.c srcs/free.c srcs/check.c srcs/init.c

SRCS_BONUS	= bonus/main_bonus.c bonus/check_bonus.c bonus/utils_bonus.c \
			bonus/timer_bonus.c bonus/init_bonus.c bonus/free_bonus.c \
			bonus/semaphores.c bonus/routine_bonus.c bonus/printer_bonus.c \
			bonus/death_bonus.c

CC	= clang

FLAGS	= -Wall -Werror -Wextra

HEADER	= -I includes/

LIBS	= -lpthread

OBJ	= $(SRCS:.c=.o)

OBJ_BONUS	= $(SRCS_BONUS:.c=.o)

all:	$(NAME)

bonus:	$(BONUS)

.c.o :	
		@printf "\033[0;33mGenerating Philosopher's objects... %-33.33s\r" $@
		@$(CC) $(FLAGS) $(HEADER) -c $< -o $(<:.c=.o)

$(NAME): $(OBJ)
		@$(CC) $(FLAGS) $(HEADER) $(OBJ) -o $(NAME) $(LIBS)
		@echo "\nBuilding philo : \033[32mOK\033[0m"

$(BONUS): $(OBJ_BONUS)
		@$(CC) $(FLAGS) $(HEADER) $(OBJ_BONUS) -o $(BONUS) $(LIBS)
		@echo "\nBuilding philo with bonus: \033[32mOK\033[0m"

clean:	
	@rm -rf $(OBJ) $(OBJ_BONUS)
	@echo "Delete OBJ files : \033[32mOK\033[0m"

fclean:	clean
	@rm -rf $(NAME) $(BONUS)
	@echo "Delete philosopher : \033[32mOK\033[0m"

re:	fclean all

run:	$(NAME)
	./philo 2 800 100 100

.PHONY:	all clean fclean re bonus
