/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 19:51:47 by rpunet            #+#    #+#             */
/*   Updated: 2021/04/09 23:35:50 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_get_input(char **line)
{
	ft_printf("MINIsh > ");
	if (get_next_line(0, line) == -1)
		return (1);
	return (0);
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

/* 	
** 	ESTA PARTE IRIA EN LA LINEA 81
** 	
** 	t_lex	aux = lexer;
** 	while (aux.list_token !=  NULL)
** 	{
** 		ft_printf("%s  ", aux.list_token->data);
** 		ft_printf("%d  ", aux.list_token->type);
** 		ft_printf("%p  \n", aux.list_token->data);
** 		aux.list_token = aux.list_token->next;
** 	}
** 	ft_printf("el lexer ha terminado, interrupcion de bucle-----------");
** 		continue;
** 	ft_printf("este es el input:  %s\n\n", line                            );
*/

int	main(int argc, char **argv)
{
	char		*line;
	t_lex		lexer;
	t_ASTnode	*syntax_tree;

	if (argc > 1 && !ft_strcmp(argv[1], "-c"))
		line = argv[2];
	while (1)
	{
		if (argc == 1)
			if (ft_get_input(&line))
				return (0);
		if (ft_lexer(line, &lexer, ft_strlen(line)))
			ft_printf("error");
		if (!ft_parser(&lexer, &syntax_tree))
			ft_execute(syntax_tree);
		ASTdelete(syntax_tree);
		tok_delete(lexer.list_token);
		if (argc > 1)
			break ;
	}
	return (0);
}
