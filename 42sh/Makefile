# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cnkosi <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/20 12:43:08 by cnkosi            #+#    #+#              #
#    Updated: 2017/09/20 12:43:11 by cnkosi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 42sh

HEADER = 42sh.h

SRC = main.c	42sh.h

OBJ = $(SRC:%.c=%.o)

LIBFT = libft/

CFLAGS = -Wextra -Wall -Werror

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIBFT)
	@cc $(CFLAGS) -c $(SRC) $(HEADER)
	@gcc -o $(NAME) $(OBJ) -L$(LIBFT) -ltf
	@clear
	@echo "42sh is compiled successfully"

clean:
	make -C $(LIBFT) clean
	@rm -f $(OBJ)
	@clear
	@echo "42sh cleaned successfully"

fclean: clean
	make -C $(LIBFT) fclean
	@rm -f $(NAME)
	@clear
	@echo "42sh is fully cleaned"

re: fclean all
	@clear
	@echo "42sh is recompiled successfully"

norm:
	@clear
	@echo "norminette 42sh"
	@norminette 42sh.h 42sh.c main.c
