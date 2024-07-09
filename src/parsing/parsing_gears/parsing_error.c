/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 02:35:05 by tauer             #+#    #+#             */
/*   Updated: 2024/07/09 02:51:08 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/all.h>

bool	cells_empty_char(t_mini *mini, char *raw_line, char c)
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
			return (mini->print("\nfound empty '%c'\n",c ), true);
		else if (raw_line[index] == c)
			empty = true;
	}
	if (comp == c)
		return (mini->print("\nfound empty '%c'\n",c ), true);
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
			return (mini->print("Found invalid redirect '<<<' '>>>'\n"), true);
		current = current->next;
	}
	return (false);
}
