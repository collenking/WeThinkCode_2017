# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cnkosi <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/08/30 11:02:20 by cnkosi            #+#    #+#              #
#    Updated: 2017/09/11 17:40:12 by cnkosi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

HEADER = minishell.h

SRC = main.c	minishell.c		ft_echo.c	ft_env.c	builtins.c	ft_chdir.c\
	  ft_execve.c

OBJ = $(SRC:%.c=%.o)

LIBFT = libft/

CFLAGS = -Wextra -Wall -Werror

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIBFT)
	@gcc $(CFLAGS) -c $(SRC) $(HEADER)
	@gcc -o $(NAME) $(OBJ) -L$(LIBFT) -lft
	@clear
	@echo "Your minishell has been successfully compiled"

clean:
	@rm -f $(OBJ)
	@rm -f *.h.gch
	make -C $(LIBFT) clean
	@clear
	@echo "Objects files are removed"

fclean: clean
	@rm -f $(NAME)
	make -C $(LIBFT) fclean
	@clear
	@echo "Your minishell is now clean"

re: fclean all
	@clear
	@echo "Your minishell has been recompiled"

norm:
	@echo "Norminette minishell"
	@clear
	@norminette	minishell.h main.c	minishell.c
