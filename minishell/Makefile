# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpunet <rpunet@student.42madrid.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/20 20:00:18 by rpunet            #+#    #+#              #
#    Updated: 2021/06/12 00:52:41 by rpunet           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= minishell
SRCS		= minishell.c lexer.c parser.c executor.c exit.c builtins.c export2.c
LIBFT_PATH	= ./libft/


all: clean
	gcc -Wall -Wextra -Werror -g -fsanitize=address -L $(LIBFT_PATH) -I . ${SRCS} -lft -o ${NAME}

clean:
		@rm -f $(NAME)

