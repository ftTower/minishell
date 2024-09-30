/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniformat_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 23:37:13 by tauer             #+#    #+#             */
/*   Updated: 2024/08/16 23:29:31 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/all.h>

void	handle_dollar_in_quotes(t_mini *mini, t_char **list ,t_char **current)
{
	//! gere le dollar simple quand il est seul dans des quotes
	if ((*current)->c == '$' && ((*current)->type_quotes == TYPEQUOTES_DOUBLE_QUOTED || (*current)->type_quotes == TYPEQUOTES_SINGLE_QUOTED))
		(*current)->type_quotes = TYPEQUOTES_SINGLE_QUOTED;
	//! supprime le dollar sil est a cote dune quote
	else if ((*current)->c == '$' && (*current)->next && ((*current)->next->c == '"' || (*current)->next->c == (char)39))
		t_char_del_pos(mini, list, (*current)->pos);
}

void	preserve_var_backslash(t_mini *mini, t_char **list, t_char **current)
{
	//* si backslash dollar dans double quote ou unquoted preserve le dollar et variable 
	if ((*current) && (*current)->next && (*current)->c == '\\'
		&& (*current)->next->c && (*current)->next->c == '$'
		&& (((*current)->type_quotes == TYPEQUOTES_UNQUOTED
		&& (*current)->next->type_quotes == TYPEQUOTES_UNQUOTED) \
		|| ((*current)->type_quotes == TYPEQUOTES_DOUBLE_QUOTED
		&& (*current)->next->type_quotes == TYPEQUOTES_DOUBLE_QUOTED)))
	{
		*current = (*current)->next;
		t_char_del_pos(mini, list, (*current)->pos - 1);
		(*current)->type_quotes = TYPEQUOTES_TO_KEEP;
		*current = (*current)->next;
		while (*current && (*current)->type_quotes == TYPEQUOTES_DOUBLE_QUOTED
		&& is_alpha((*current)->c))
		{
			(*current)->type_quotes = TYPEQUOTES_TO_KEEP;
			*current = (*current)->next;
		}
		*current = *list;
	}
}

void	t_char_del_pos_safe(t_mini *mini, t_char **list, t_char **current)
{
	t_char *next;

	next = (*current)->next; 
	t_char_del_pos(mini, list, (*current)->pos);
	*current = next; 
}

void	handle_backslash_in_quotes(t_mini *mini, t_char **list ,t_char **current)
{
	//* supprime le backslash si next est différent de backslash ou dollar ou char à garder
	if ((*current)->c == '\\' && (*current)->next && (*current)->next->c != '\\' \
		&& (*current)->next->c != '$' && (*current)->type_quotes != TYPEQUOTES_TO_KEEP)
		t_char_del_pos_safe(mini, list, current);
	//* si double backslash, supprime le premier backslash et préserve le deuxième
	else if ((*current)->c == '\\' && (*current)->next && (*current)->next->c == '\\')
	{
		*current = (*current)->next;
		(*current)->type_quotes = TYPEQUOTES_TO_KEEP;
		t_char_del_pos_safe(mini, list, current);
	}
	preserve_var_backslash(mini, list, current);
}

void	handle_in_quotes(t_mini *mini, t_char **list)
{
	t_char	*current;

	current = *list;
	while (current)
	{
		handle_dollar_in_quotes(mini, list , &current);
		if (current == NULL) break; // Check if current is NULL after handle_dollar_in_quotes
		handle_backslash_in_quotes(mini, list , &current);
		if (current == NULL) break; // Check if current is NULL after handle_backslash_in_quotes
		current = current->next;
	}
}

void	t_char_del_quotes(t_mini *mini, t_char **list)
{
	t_char	*current;

	current = *list;
	while (current)
	{
		if ((current->c == (char)39 || current->c == '"')
			&& current->type_quotes != TYPEQUOTES_TO_KEEP)
		{
			current = current->next;
			t_char_del_pos(mini, list, current->pos - 1);
		}
		else
			current = current->next;
	}
}

bool	t_char_list_format_quotes(t_mini *mini, t_char **list)
{
	t_char_set_pos(*list);
	t_char_identify_typequote(*list);
	handle_in_quotes(mini, list);
	t_char_del_quotes(mini, list);
	return (false);
}
