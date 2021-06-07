# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/20 20:00:18 by rpunet            #+#    #+#              #
#    Updated: 2021/06/07 23:09:52 by jcarrete         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= minishell
SRCS		= minishell.c lexer.c parser.c executor.c exit.c builtins.c export.c
LIBFT_PATH	= ./libft/


all: clean
	gcc -Wall -Wextra -Werror -g -fsanitize=address -L $(LIBFT_PATH) -I . ${SRCS} -lft -o ${NAME}

clean:
		@rm -f $(NAME)

