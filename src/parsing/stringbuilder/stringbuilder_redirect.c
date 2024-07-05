/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringbuilder_redirect.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:18:43 by tauer             #+#    #+#             */
/*   Updated: 2024/07/05 15:21:35 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/all.h>

bool	redirect_unspacer(t_mini *mini, t_pipe *pipe)
{
	t_char	*current;
	t_char	*tmp;

	current = pipe->raw_words;
	while (current)
	{
		if ((current->c == '<' || current->c == '>') && current->next
			&& (current->next->c == ' '))
		{
			tmp = current->next;
			current->next = current->next->next;
			mini->free(mini, tmp);
		}
		if ((current->c == '<' || current->c == '>') && !current->next)
			return (mini->print("found empty redirect...\n"), true);
		current = current->next;
	}
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

