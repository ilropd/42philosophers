# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: irozhkov <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/25 14:49:12 by irozhkov          #+#    #+#              #
#    Updated: 2024/06/27 13:56:08 by irozhkov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

HEADER = $(SRC_DIR)/philo.h

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = ../philo
SRC = $(shell find $(SRC_DIR) -name "*.c" ! -name "*_bonus.c")

OBJ = $(patsubst %.c,%.o,$(SRC))

REMOVE = rm -f

GREEN = \033[0;32m
DEFAULT = \033[0m

all: $(NAME)

%.o: %.c $(HEADER) Makefile
	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

$(NAME): $(OBJ) $(HEADER)
	@echo "---> object files $(GREEN)CREATED$(DEFAULT)\n"
	$(CC) $(OBJ) -o $(NAME)
	@echo "---> $(NAME) is $(GREEN)AVAILABLE NOW$(DEFAULT)\n"

clean:
	$(REMOVE) $(shell find $(SRC_DIR) -name "*.o")
	@echo "---> object files $(GREEN)DELETED$(DEFAULT)\n"

fclean: clean
	$(REMOVE) $(NAME)
	@echo "---> $(NAME) $(GREEN)DELETED$(DEFAULT)\n"

re: fclean all

.PHONY: all clean fclean re
