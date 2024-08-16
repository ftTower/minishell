/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_invalid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 02:35:05 by tauer             #+#    #+#             */
/*   Updated: 2024/08/16 23:23:07 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/all.h>

bool	cells_empty_char(char *raw_line, char c)
{
	ssize_t	index;
	bool	empty;
	char	comp;

	comp = ' ';
	empty = true;
	index = -1;
	while (raw_line[++index])
	{
		if (raw_line[index] != ' ')
			comp = raw_line[index];
		if (raw_line[index] != ' ' && raw_line[index] != c)
			empty = false;
		else if (raw_line[index] == c && empty)
			return (true);
		else if (raw_line[index] == c)
			empty = true;
	}
	if (comp == c)
		return (true);
	return (false);
}

bool	invalid_redirect(t_mini *mini, t_char **list)
{
	t_char	*current;

	current = (*list);
	while (current)
	{
		if (current && current->next && current->next->next
			&& (current->c == '<' || current->c == '>')
			&& (current->next->c == '<' || current->next->c == '>')
			&& (current->next->next->c == '<' || current->next->next->c == '>'))
			return (handle_error(mini, t_char_list_to_str(mini, *list), ERROR_TOO_MANY_REDIRECT),true);
		current = current->next;
	}
	return (false);
}
