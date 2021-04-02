/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 17:46:37 by jcarrete          #+#    #+#             */
/*   Updated: 2020/12/16 19:32:45 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	complete_line(char **buff, int pos, char **line)
{
	char	*temp;
	int		len;

	(*buff)[pos] = '\0';
	*line = ft_strdup(*buff);
	if ((len = ft_strlen(*buff + pos + 1)) == 0)
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

	if (*buff && (cut = ft_strchr_pos(*buff, '\n')) >= 0)
		return (complete_line(buff, cut, line));
	if (*buff)
	{
		*line = *buff;
		*buff = NULL;
		return (0);
	}
	*line = ft_strdup("");
	return (0);
}

int			ft_get_next_line(int fd, char **line)
{
	static char	*buff[32];
	char		*stack;
	int			bytes;
	int			cut;

	if (fd < 0 || fd > 32 || !line || 2 <= 0\
		|| !(stack = (char *)malloc(sizeof(char) * (2 + 1))))
		return (-1);
	while ((bytes = read(fd, stack, 2)) > 0)
	{
		stack[bytes] = '\0';
		buff[fd] = ft_strjoin_gnl(buff[fd], stack);
		if ((cut = ft_strchr_pos(buff[fd], '\n')) >= 0)
		{
			stack = ft_memfree(stack, NULL);
			return (complete_line(&buff[fd], cut, line));
		}
	}
	stack = ft_memfree(stack, NULL);
	if (bytes < 0)
		return (-1);
	return (found_eof(&buff[fd], line));
}
