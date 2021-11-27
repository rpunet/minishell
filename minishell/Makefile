# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/20 20:00:18 by rpunet            #+#    #+#              #
#    Updated: 2021/11/27 20:42:13 by jcarrete         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= minishell
SRCS		= minishell.c lexer.c parser.c executor.c exit.c builtins.c export2.c
LIBFT_PATH	= ./libft/


all: clean
	gcc -Wall -Wextra -Werror -g -fsanitize=address -L $(LIBFT_PATH) -I . ${SRCS} -lft -lreadline -o ${NAME}

clean:
		@rm -f $(NAME)

