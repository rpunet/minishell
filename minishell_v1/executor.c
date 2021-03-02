/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpunet <rpunet@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 16:54:18 by rpunet            #+#    #+#             */
/*   Updated: 2021/03/02 21:41:09 by rpunet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	execute_CMD(t_ASTnode *cmd_node, int in, int out)
{
	int			i;
	char		**args;
	t_ASTnode	*curr;

	//if (   REDIR; INDIR)
	//...				aquií irán las redireecciones un poco más adelante que bastante liado esta esto ya...
	//					seguramente habŕa que pasar más parametros o ejecutar todo desde aquí



	if (cmd_node != NULL || cmd_node->type == CMDNAME_NODE)
	{
		pid_t pid;

		curr = cmd_node;
		i = 0;
		while (curr != NULL && (curr->type == CMDNAME_NODE || curr->type == TOKEN_NODE))
		{
			i++;
			curr = curr->right;
		}
		args = malloc(sizeof(char *) * (i + 1));			// checkear el malloc (habra que revisar todos los retornos de funciones para que retornes erorres...me parece que voids poquitos :((
		curr = cmd_node;
		i = 0;
		while (curr != NULL && (curr->type == CMDNAME_NODE || curr->type == TOKEN_NODE))
		{
			args[i] = ft_strdup(curr->data);											// esto hay que liberarlo FREEE y el malloc anterior
			curr = curr->right;
			i++;
		}
		args[i] = NULL;
		if (i > 0)
		{
			if ((pid = fork()) == 0)
			{
				if (in != 0)
					dup2(in, STDIN_FILENO);
				if (out != 1)
					dup2(out, STDOUT_FILENO);
				//close(in), close(out);
				if (execvp(args[0], args) == -1) // de momeno con EXECVP en lugar de execve
				{
					ft_printf("error de exec");
					return ; //errorrrrr habrá que salir y restaurar el STDOUT FILENO para que salga el error por pantalla
				}
			}
			//else if (pid < 0){ return error fork()}
			while (waitpid(pid, NULL, 0) <= 0); //ejecute la espera hasta que salga exitosa y retorne el pid que cambia de estado
		}
	}

}

void	execute_INSTR(t_ASTnode *instr)			// PIPING tripping
{
	t_ASTnode	*curr;
	int			fds[2];
	int			pipe_ends[2];

	int p = pipe(fds);
	pipe_ends[1] = fds[WRITE];					// para almacen temporal de fds de pipes que comparten comandos consecutivos
	pipe_ends[0] = fds[READ];
	execute_CMD(instr->left, STDIN_FILENO, fds[WRITE]);
	curr = instr->right;
	while (curr != NULL && curr->type == PIPE_NODE)
	{
		close(fds[WRITE]);
		pipe(fds);
		execute_CMD(curr->left, pipe_ends[0], fds[WRITE]);		//comando a ejecucion con el fd READ del pipe anterior que se almacena en pipe_ends, y el WRITE actual
		close(pipe_ends[0]);
		pipe_ends[0] = fds[READ];
		curr = curr->right;
	}
	close(fds[WRITE]);
	execute_CMD(curr, fds[READ], STDOUT_FILENO);
	close(fds[READ]);
}

void	execute_JOB(t_ASTnode *job)
{
	if (job == NULL)
		return ;
	if (job->type == PIPE_NODE)
	{
		execute_INSTR(job);
	//	execute_JOB(job->right);
	}
	else
	{
		execute_CMD(job, STDIN_FILENO, STDOUT_FILENO);
	}
}

void	execute_SEQ(t_ASTnode *seq)
{
	if (seq == NULL)
		return ;
	if (seq->type == SEQ_NODE)
	{
		execute_JOB(seq->left);
		execute_SEQ(seq->right);
	}
	else
		execute_JOB(seq);
}

void	ft_execute(t_ASTnode *syntax_tree)
{
	execute_SEQ(syntax_tree);
}
