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

// void	t_char_list_handle_in_quotes(t_mini *mini, t_char **list)
// {
// 	t_char *current;

// 	current = *list;
// 	while(current)
// 	{
// 		if (current->type_quotes == TYP)
// 		current = current->next;
// 	}
// }

void	handle_in_quotes(t_mini *mini, t_char **list)
{
	t_char	*current;

	current = *list;
	while (current)
	{
		if (current->c == '\\' && current->next && current->next->c == '\\')
		{
			current = current->next;
			current->type_quotes = TYPEQUOTES_TO_KEEP;
			t_char_del_pos(mini, list, current->pos - 1);
		}
		if (current->c && current->next && current->c == '\\'
			&& current->next->c == '$'
			&& ((current->type_quotes == TYPEQUOTES_DOUBLE_QUOTED
					&& current->next->type_quotes == TYPEQUOTES_DOUBLE_QUOTED)))
		{
			current = current->next;
			t_char_del_pos(mini, list, current->pos - 1);
			current->type_quotes = TYPEQUOTES_TO_KEEP;
			current = current->next;
			while (current && current->type_quotes == TYPEQUOTES_DOUBLE_QUOTED
				&& current->c != '"' && current->c != '\\' && current->c != '|' && current->c != '$')
			{
				
				current->type_quotes = TYPEQUOTES_TO_KEEP;
				current = current->next;
			}
			current = *list;
		}
		else if (current->c && current->next && current->c == '\\'
			&& current->next->c == '$'
			&& ((current->type_quotes == TYPEQUOTES_UNQUOTED
					&& current->next->type_quotes == TYPEQUOTES_UNQUOTED)))
		{
			current = current->next;
			t_char_del_pos(mini, list, current->pos - 1);
			while (current && current->type_quotes == TYPEQUOTES_UNQUOTED
				&& current->c != '\\' && current->c != ' ')
			{
				current->type_quotes = TYPEQUOTES_TO_KEEP;
				current = current->next;
			}
			current = *list;
		}
		else
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