/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniformat_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 23:37:13 by tauer             #+#    #+#             */
/*   Updated: 2024/08/05 01:51:37 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/all.h>

void	get_quotes_bool(t_char *current, bool *double_quote, bool *single_quote)
{
	if (current->c == '"')
	{
		if (!(*double_quote))
			*double_quote = true;
		else
			*double_quote = false;
	}
	else if (current->c == (char)39)
	{
		if (!(*single_quote))
			*single_quote = true;
		else
			*single_quote = false;
	}
}

bool	handle_in_quotes(t_mini *mini, t_char **list)
{
	t_char	*current;
	bool	double_quote;
	bool	single_quote;

	current = (*list);
	double_quote = false;
	single_quote = false;
	while (current)
	{
		get_quotes_bool(current, &double_quote, &single_quote);
		if (!double_quote && current->c == '$' && current->next->c == '"')
		{
			t_char_del_pos(mini, list, current->pos);
			current = (*list);
		}
		else if (double_quote && current->c == '\\' && current->next
			&& current->next->c == '\\')
		{
			t_char_del_pos(mini, list, current->pos);
			current = (*list);
		}
		else if (double_quote && current->c == '\\' && current->next
			&& current->next->c == '$')
		{
			t_char_del_pos(mini, list, current->pos);
			current = (*list);
		}
		current = current->next;
	}
	return (false);
}

t_char	*get_to_next_char(t_char *list, char c)
{
	t_char	*current;
	t_char	*next;

	current = list;
	while (current)
	{
		if (current->c == c)
		{
			next = current->next;
			return (next);
		}
		current = current->next;
	}
	return (NULL);
}

bool	remove_all_quotes(t_mini *mini, t_char **list)
{
	t_char	*current;

	current = (*list);
	while (current)
	{
		if (current->c == (char)39)
		{
			t_char_del_pos(mini, list, current->pos);
			current = get_to_next_char(*list, (char)39);
		}
		else if (current->c == '"')
		{
			t_char_del_pos(mini, list, current->pos);
			current = get_to_next_char(*list, '"');
		}
		if (current)
			current = current->next;
	}
	return (false);
}

bool	t_char_list_format_quotes(t_mini *mini, t_char **list)
{
	t_char_set_pos(*list);
	if (handle_in_quotes(mini, list) || remove_all_quotes(mini, list))
		return (true);
	return (false);
}