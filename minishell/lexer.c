/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpunet <rpunet@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 22:27:46 by rpunet            #+#    #+#             */
/*   Updated: 2021/06/13 01:28:27 by rpunet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_value(char **envp, char *key)
{
	char	*find;

	while (*envp)
	{
		find = read_key(*envp);
		if (!ft_strcmp(find, key))
		{
			return (ft_substr(*envp, ft_strlen(find) + 1, ft_strlen(*envp)));
		}
		envp++;
	}
	free(find);
	return (NULL);
}

void	expand_vars(char **cmd)
{
	char	*var_value;
	char	*new_cmd;
	char	*aux;
	int		i;

	char *find = ft_strchr(*cmd, '$');
	if (find)
	{
		find++;
		if (find)
		{
			var_value = getenv(find);		//find_value
			// var_value = find_value(envp, find);
			i = ft_strlen(*cmd) - ft_strlen(find) - 1;
			if (var_value)
			{
				if (!(new_cmd = malloc(i + ft_strlen(var_value))))
					return ;
				new_cmd = ft_memmove(new_cmd, *cmd, i);
				aux = new_cmd;
				new_cmd = ft_memmove(new_cmd + (i), var_value, ft_strlen(var_value));
				free(*cmd);
				*cmd = aux;
			}
			else
			{
				aux = ft_substr(*cmd, 0, i);
				free(*cmd);
				*cmd = aux;
			}
		}
	}
}

t_tok	*tok_init(int datasize)
{
	t_tok	*token;

	token = malloc(sizeof(t_tok));
	if (token == NULL)
		return (NULL);
	token->data = malloc(datasize + 1);
	if (token->data == NULL)
		return (NULL);
	token->type = NULTOK;
	token->next = NULL;
	return (token);
}

void	tok_delete(t_tok *token)
{
	if (token != NULL)
	{
		token->data = ft_memfree(token->data, NULL);
		tok_delete(token->next);
		token = ft_memfree(token, NULL);
	}
}

int	ft_lexer(char *line, t_lex *lexer, int size)
{
	t_tok	*token;
	int		c;
	int		i;
	int		j;
	int		state;
	int		last_quoted = 0;

	token = tok_init(size);
	lexer->list_token = token;
	state = GENERAL;
	i = 0;
	j = 0;
	while (line[i] != 0)
	{
		c = (line[i]);
		if (state == GENERAL)
		{
			if (c == '\'')
			{
				state = QUOTED;
				token->type = TOKEN;
			}
			else if (c == '\"')
			{
				state = DQUOTED;
				token->type = TOKEN;
			}
			else if (c == '\\')
			{
				token->data[j] = line[++i];
				j++;
				token->type = TOKEN;
			}
			else if (c == ' ')
			{
				if (j > 0)
				{
					token->data[j] = 0;
					if (!last_quoted)
						expand_vars(&token->data);
					token->next = tok_init(size - i);
					token = token->next;
					last_quoted = 0;
					j = 0;
				}
			}
			else if (c == ';' || c == '>' || c == '<' || c == 66 || c == '|')	//	 (el 66 seria el >> que hay que detallar)
			{
				if (j > 0)
				{
					token->data[j] = 0;
					if (!last_quoted)
						expand_vars(&token->data);
					token->next = tok_init(1);
					token = token->next;
					last_quoted = 0;
					j = 0;
				}
				token->data[0] = (char)c;
				token->data[1] = 0;
				token->type = c;
				token->next = tok_init(size - i);
				token = token->next;
			}
			else
			{
				token->data[j] = (char)c;
				j++;
				token->type = TOKEN;
			}
		}
		else if (state == QUOTED)
		{
			if (c == '\'')
			{
				last_quoted = 1;
				state = GENERAL;
			}
			else
				token->data[j++] = (char)c;
		}
		else if (state == DQUOTED)
		{
			if (c == '\"')
				state = GENERAL;
			else
				token->data[j++] = (char)c;
		}
		// else if (state == VAR)
		// {
		// 	if (c == ' ')
		// 		state = GENERAL;
		// 	else
		// 		token->data[j++] = (char)c;
		// }
		i++;
	}
	token->data[j] = 0;
	if (!last_quoted)
		expand_vars(&token->data);
	return (0);
}
