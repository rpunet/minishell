/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 22:19:55 by jcarrete          #+#    #+#             */
/*   Updated: 2022/02/03 18:37:11 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bst	*create_bst_node(void)
{
	t_bst	*statement;

	statement = malloc(sizeof(t_bst));
	if (statement == NULL)
		return (NULL);
	statement->operator_child = 0;
	statement->operator_next = 0;
	statement->tree = NULL;
	statement->child = NULL;
	statement->next = NULL;
	statement->prev = NULL;
	return (statement);
}

static void	advance_one(t_tok **curr, t_tok **prev, t_tok **ante)
{
	if (*prev != NULL)
		*ante = *prev;
	if (*curr != NULL)
		*prev = *curr;
	if ((*curr)->next)
		*curr = (*curr)->next;
}

static void	handle_open_bracket(t_bst **bst, t_tok **curr, \
								t_tok **prev, t_tok **ante)
{
	t_bst	*actual_bst;

	actual_bst = *bst;
	if ((*curr)->next->type == T_BRAKET_CLOSE)
		exit_program(get_minishell(NULL), F_SHELL, E_PARSER, "(");
	while ((*curr)->next->type == T_BRAKET_OPEN)
		*curr = (*curr)->next;
	actual_bst->operator_child = (*prev)->type;
	(*ante)->next = NULL;
	actual_bst->tree = gr_seq();
	actual_bst->child = create_bst_node();
	*bst = actual_bst->child;
	g_current_tok = (*curr)->next;
}

static void	handle_close_bracket(t_bst **bst, t_tok **curr, t_tok **prev)
{
	t_bst	*actual_bst;
	t_bst	*link;

	actual_bst = *bst;
	(*prev)->next = NULL;
	actual_bst->tree = gr_seq();
	g_current_tok = NULL;
	if ((*curr)->next == NULL)
		return ;
	if ((*curr)->next->type == T_BRAKET_OPEN)
		exit_program(get_minishell(NULL), F_SHELL, E_PARSER, ")");
	link = actual_bst->prev;
	while ((*curr)->next->type == T_BRAKET_CLOSE)
	{
		*curr = (*curr)->next;
		link = link->prev;
	}
	while (link->next != NULL)
		link = link->prev;
	link->operator_next = (*curr)->next->type;
	link->next = create_bst_node();
	*bst = link->next;
	g_current_tok = (*curr)->next->next;
}

void	parse_brackets(t_minishell *shell)
{
	t_bst	*curr_bst;
	t_tok	*curr_tok;
	t_tok	*prev_tok;
	t_tok	*anteprev_tok;

	curr_bst = shell->bst;
	prev_tok = NULL;
	anteprev_tok = NULL;
	curr_tok = shell->lexer.list_token;
	while (curr_tok && curr_tok->type == T_BRAKET_OPEN)
		curr_tok = curr_tok->next;
	g_current_tok = curr_tok;
	while (curr_tok)
	{
		while (curr_tok && (curr_tok->type != T_BRAKET_OPEN && \
							curr_tok->type != T_BRAKET_CLOSE))
			advance_one(&curr_tok, &prev_tok, &anteprev_tok);
		if (curr_tok && curr_tok->type == T_BRAKET_OPEN)
			handle_open_bracket(&curr_bst, &curr_tok, &prev_tok, &anteprev_tok);
		else if (curr_tok && curr_tok->type == T_BRAKET_CLOSE)
			handle_close_bracket(&curr_bst, &curr_tok, &prev_tok);
		advance_one(&curr_tok, &prev_tok, &anteprev_tok);
	}
}
