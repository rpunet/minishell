/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 16:05:03 by jcarrete          #+#    #+#             */
/*   Updated: 2021/12/12 16:09:04 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(char **args, char ***envp)
{
	char	*find;

	find = find_variable(*envp, *args, NULL);
	if (*args && find)
		delete_var(envp, *args);
	free(find);
	return (FALSE);
}
