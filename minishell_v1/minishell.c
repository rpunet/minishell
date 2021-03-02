/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpunet <rpunet@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 19:51:47 by rpunet            #+#    #+#             */
/*   Updated: 2021/03/02 17:35:20 by rpunet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	ft_get_input(char **line)
{
	ft_printf("MINIsh > ");
	if (get_next_line(0, line) == -1)
			return 1;
	return 0;
}

t_tok	*tok_init(int datasize)
{
	t_tok *token;

	if ((token = malloc(sizeof(t_tok))) == NULL)
		return (NULL);
	if ((token->data = malloc(datasize + 1)) == NULL)
		return (NULL);
	token->type = NULTOK;
	token->next = NULL;
	return (token);
}

void	tok_delete(t_tok *token)
{
	if (token != NULL)
	{
		free(token->data);
		tok_delete(token->next);
		free(token);
	}
}

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
				return 0;
		if (ft_lexer(line, &lexer, ft_strlen(line)))
			ft_printf("error");


		t_lex	aux = lexer;
		while (aux.list_token !=  NULL)
		{
			ft_printf("%s  ", aux.list_token->data);
			ft_printf("%d  ", aux.list_token->type);
			ft_printf("%p  \n", aux.list_token->data);
			aux.list_token = aux.list_token->next;
		}
	//ft_printf("el lexer ha terminado, interrupcion de bucle-----------");
		//continue;



		ft_printf("este es el input:  %s\n\n", line                            );
		if (!ft_parser(&lexer, &syntax_tree))
			ft_execute(syntax_tree);
		ASTdelete(syntax_tree);		//meter al final de execute antes de salir para limpiar main
		tok_delete(lexer.list_token);
		if (argc > 1)			// esto es para que salga si la ejecucion es con -c
			break;
	}
	return 0;
}
