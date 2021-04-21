/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 17:46:37 by jcarrete          #+#    #+#             */
/*   Updated: 2021/04/21 18:42:03 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	complete_line(char **buff, int pos, char **line)
{
	char	*temp;
	int		len;

	(*buff)[pos] = '\0';
	*line = ft_strdup(*buff);
	len = ft_strlen(*buff + pos + 1);
	if (len == 0)
	{
		(*buff) = ft_memfree(*buff, NULL);
		return (1);
	}
	temp = ft_strdup(*buff + pos + 1);
	(*buff) = ft_memfree(*buff, temp);
	return (1);
}

static int	found_eof(char **buff, char **line)
{
	int		cut;

	if (*buff)
	{
		cut = ft_strchr_pos(*buff, '\n');
		if (cut >= 0)
			return (complete_line(buff, cut, line));
		*line = *buff;
		*buff = NULL;
		return (0);
	}
	*line = ft_strdup("");
	return (0);
}

static int	gnl_loop(char *stack, int fd, char **line)
{
	static char	*buff[32];
	int			bytes;
	int			cut;

	bytes = read(fd, stack, GNL_BUFFER_SIZE);
	while (bytes > 0)
	{
		stack[bytes] = '\0';
		buff[fd] = ft_strjoin_gnl(buff[fd], stack);
		cut = ft_strchr_pos(buff[fd], '\n');
		if (cut >= 0)
		{
			stack = ft_memfree(stack, NULL);
			return (complete_line(&buff[fd], cut, line));
		}
		bytes = read(fd, stack, GNL_BUFFER_SIZE);
	}
	stack = ft_memfree(stack, NULL);
	if (bytes < 0)
		return (-1);
	return (found_eof(&buff[fd], line));
}

int	ft_get_next_line(int fd, char **line)
{
	char		*stack;

	if (fd < 0 || fd > 32 || !line || GNL_BUFFER_SIZE <= 0)
		return (-1);
	stack = (char *)(malloc(sizeof(char) * (GNL_BUFFER_SIZE + 1)));
	if (stack == NULL)
		return (-1);
	return (gnl_loop(stack, fd, line));
}
