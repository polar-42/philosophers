# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fle-tolg  <fle-tolg@student.42angouleme    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/27 11:57:23 by fle-tolg          #+#    #+#              #
#    Updated: 2022/12/16 19:51:00 by fle-tolg         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED = \033[0;31m
GREEN = \033[0;32m
BLUE = \033[0;34m
END = \033[0m

NAME = philosophers

CFLAGS = -Wextra -Wall -Werror

PFLAGS = -pthread

CC = clang -g

RM = rm -f

OBJ = $(SRC:.c=.o)

SRC = 	philo/sources/main.c\
		philo/sources/initialize_utils.c\
		philo/sources/philo_utils.c\
		philo/sources/thread_utils.c\
		philo/sources/time_utils.c\
		philo/sources/philo_actions.c\
		philo/sources/table_utils.c

all : $(NAME) $(LIBFT)

bonus : $(NAME_B) $(LIBFT)

%.o: %.c
	@$(CC) $(CFLAGS) $(PFLAGS) -c -o $@ $<

$(NAME) : ${OBJ}
	@$(CC) $(CFLAGS) $(PFLAGS) $(OBJ) -o $(NAME)
	@echo "${GREEN}$(NAME) compilated with success"

clean :
	@$(RM) $(OBJ)
	@echo "${RED}$(NAME) clean"

fclean :
	@$(RM) $(OBJ) $(NAME)
	@echo "${RED}$(NAME) fclean"

norme :
	norminette philo

re :	fclean all

.PHONY :
	all clean fclean norme re
