/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpunet <rpunet@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 19:51:47 by rpunet            #+#    #+#             */
/*   Updated: 2021/06/13 23:14:28 by rpunet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_get_input(char **line)
{
	ft_printf("MINIsh > ");
	if (ft_get_next_line(0, line) == -1)
		return (1);
	return (0);
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

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_lex		lexer;
	t_ASTnode	*syntax_tree;
	char		**envp_dup;

	if (argc > 1 && !ft_strcmp(argv[1], "-c"))				//  FALTA comprobacion argumentos para que no pete
		line = argv[2];
	envp_dup = ft_envdup(envp, double_len(envp), 1, NULL);
	// for (int i = 0; envp_dup[i]; i++)
	// 	ft_printf("%s\n", envp_dup[i]);
	// free_char_array(envp, double_len(envp));
	// free_char_array(envp_dup, double_len(envp_dup));
	envp = envp_dup;														// ??????
	// for (int i = 0; envp[i]; i++)
	// 	ft_printf("%s\n", envp[i]);
	while (1)
	{
		if (argc == 1)
			if (ft_get_input(&line))
				return (0);
		if (ft_lexer(line, &lexer, ft_strlen(line), envp_dup))
			ft_printf("error");
		if (!ft_parser(&lexer, &syntax_tree))
			ft_execute(syntax_tree, &envp_dup);
		else
			ft_putstr_fd("MINIsh: syntax error near unexpected token `;'\n", 1);

		ASTdelete(syntax_tree);
		tok_delete(lexer.list_token);
		ft_memfree(line, NULL);
		if (argc > 1)
			break ;
	}
	return (0);
}
