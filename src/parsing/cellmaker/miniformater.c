/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniformater.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 02:13:56 by tauer             #+#    #+#             */
/*   Updated: 2024/08/08 17:52:41 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/all.h>

bool	redirect_unspacer(t_mini *mini, t_char **dst)
{
	t_char	*current;
	t_char	*tmp;

	current = (*dst);
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

bool	mini_formater(t_mini *mini, t_pipe *pipe, char **pipe_words)
{
	if (strr_to_t_char_list(mini, &pipe->raw_words, pipe_words)
		|| redirect_unspacer(mini, &pipe->raw_words) || invalid_redirect(mini,
			&pipe->raw_words) || t_char_list_format_quotes(mini,
			&pipe->raw_words) || miniformat_var(mini, &pipe->raw_words))
		// handle quotes there
		return (mini->print("failed to build string\n"), true);
	return (false);
}
