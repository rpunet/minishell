/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 19:50:37 by jcarrete          #+#    #+#             */
/*   Updated: 2021/04/04 15:33:30 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst == NULL || del == NULL)
		return ;
	(*del)(lst->content);
	free(lst);
	lst = NULL;
}

void	ft_lstdel(t_list *lst, void (*del)(void*))
{
	t_list	*next;

	while (lst != NULL)
	{
		next = lst->next;
		ft_lstdelone(lst, (*del));
		lst = next;
	}
}
