# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpunet <rpunet@student.42madrid.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/20 20:00:18 by rpunet            #+#    #+#              #
#    Updated: 2021/02/24 21:21:35 by rpunet           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= minishell
SRCS		= minishell.c builtins.c
LIBFT_PATH	= ../../libftPLUS/


all: clean
	gcc -Wall -Wextra -Werror -g ${SRCS} -I . -L $(LIBFT_PATH) -lft -o ${NAME}

clean:
		@rm -f $(NAME)

