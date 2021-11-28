/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 19:51:47 by rpunet            #+#    #+#             */
/*   Updated: 2021/11/28 13:28:49 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_get_input(char **line)
{
	char	*prompt;

	prompt = ft_strjoin("", "MINIsh > ");
	*line = readline(prompt);
	if (!line)
		return (EXIT_FAILURE);
	if (**line)
		add_history(*line);
	prompt = ft_memfree(prompt, NULL);
	return (EXIT_SUCCESS);
}

static void	sign_handler_nel(int signal)
{
	int		exit_code;
	t_pipe	std;

	exit_code = SIGINT + EXIT_STATUS;
	ft_dprintf(STDIN_FILENO, "\n");
	if (signal == SIGINT)
	{
		std.in = dup(STDIN_FILENO);
		if (std.in == -1)
			exit_failure("");
		close(STDIN_FILENO);
	}
}

static void	sign_handler_null(int signal)
{
	
}

static void	set_shell_signals(void)
{
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		exit_failure("Error");
	if (signal(SIGINT, sign_handler_nel) == SIG_ERR)
		exit_failure("Error");
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
	set_shell_signals();
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
		line = ft_memfree(line, NULL);
		if (argc > 1)
			break ;
	}
	return (0);
}
