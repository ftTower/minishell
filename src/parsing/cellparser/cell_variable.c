/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cell_variable.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 16:59:39 by tauer             #+#    #+#             */
/*   Updated: 2024/07/28 17:07:10 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/all.h>

bool	t_word_variable_handler(t_mini *mini, t_word *word)
{
	char	**splitted;
	char	*word_content;
	ssize_t	index;

	if (word->refined_word[0] == '$' && !get_envpl_var(mini, word->refined_word
			+ 1))
		return (word->refined_word = "", false);
	splitted = mini->libft->split(mini->solib, word->refined_word, '$');
	word_content = "";
	index = -1;
	while (splitted[++index])
	{
		if (get_envpl_var(mini, splitted[index]))
			mini->libft->strmcat(mini->solib, &word_content, get_envpl_var(mini,
					splitted[index]));
		else if (index == 0)
			mini->libft->strmcat(mini->solib, &word_content, splitted[index]);
	}
	if (word_content && *word_content)
		word->refined_word = word_content;
	return (false);
}

bool	t_pipe_variable_handler(t_mini *mini, t_pipe *pipe)
{
	t_word *current;

	current = pipe->words;
	while (current)
	{
		if (t_word_variable_handler(mini, current))
			return (true);
		current = current->next;
	}
	return (false);
}
