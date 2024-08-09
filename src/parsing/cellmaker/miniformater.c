/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniformater.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 02:13:56 by tauer             #+#    #+#             */
/*   Updated: 2024/08/09 23:36:19 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/all.h>

bool	redirect_unspacer(t_mini *mini, t_char **dst, t_error_list **error_list)
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
			return (add_error_to_list(mini, error_list, ERROR_EMPTY_REDIRECT,
					t_char_list_to_str(mini, *dst)), true);
		current = current->next;
	}
	return (false);
}

bool	mini_formater(t_mini *mini, t_pipe *pipe, char **pipe_words)
{
	if (strr_to_t_char_list(mini, &pipe->raw_words, pipe_words)
		|| redirect_unspacer(mini, &pipe->raw_words, &pipe->error_list)
		|| invalid_redirect(mini, &pipe->raw_words, &pipe->error_list)
		|| t_char_list_format_quotes(mini, &pipe->raw_words)
		|| t_char_list_cat_var(mini, &pipe->raw_words))
		return (true);
	return (false);
}
