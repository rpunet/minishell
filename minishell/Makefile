# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/20 20:00:18 by rpunet            #+#    #+#              #
#    Updated: 2021/04/13 22:04:01 by jcarrete         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= minishell
SRCS		= minishell.c lexer.c parser.c executor.c exit.c
LIBFT_PATH	= ./libft/


all: clean
	gcc -Wall -Wextra -Werror -g -fsanitize=address -L $(LIBFT_PATH) -I . ${SRCS} -lft -o ${NAME}

clean:
		@rm -f $(NAME)

