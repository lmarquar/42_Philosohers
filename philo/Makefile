# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: leon <lmarquar@student.42wolfsburg.de      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/03 12:20:33 by leon              #+#    #+#              #
#    Updated: 2022/05/03 12:20:36 by leon             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		:= gcc
CFLAGS	:= -Wall -Werror -Wextra
LIBS	:= -pthread
LEAKCHK	:= -fsanitize=address
SRC		:= take_argv.c philo.c philo_core.c time.c misfit.c
NAME	:= philo

all: $(NAME)
	
leaks: 
	$(CC) $(CFLAGS) $(LEAKCHK) $(LIBS) $(SRC) -o $(NAME)

re: fclean all

clean:

fclean:
	rm -f philo

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $(LIBS) $^ -o $@
