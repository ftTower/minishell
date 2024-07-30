/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cell_variable.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 16:59:39 by tauer             #+#    #+#             */
/*   Updated: 2024/07/31 01:26:38 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/all.h>

bool	t_word_variable_handler(t_mini *mini, t_word *word)
{
	char	**splitted;
	char	**splitted_quote;
	char	*word_content;
	ssize_t	index;
	ssize_t	index_quote;

	if (word->refined_word[0] == '$' && !get_envpl_var(mini, word->refined_word
			+ 1))
		return (word->refined_word = "", false);
	splitted = mini->libft->split(mini->solib, word->refined_word, '$');
	word_content = "";
	index = -1;
	while (splitted[++index])
	{
		index_quote = -1;
		splitted_quote = mini->libft->split(mini->solib, splitted[index], '"');
		print_double_tab(mini, splitted_quote);
		while (splitted_quote[++index_quote])
		{
			printf("splitted_quote[%ld]: %s\n", index_quote,
				splitted_quote[index_quote]);
			if (get_envpl_var(mini, splitted_quote[index_quote]))
				mini->libft->strmcat(mini->solib, &word_content,
					get_envpl_var(mini, splitted_quote[index_quote]));
			else
				mini->libft->strmcat(mini->solib, &word_content,
					splitted_quote[index_quote]);
		}
	}
	if (word_content && *word_content)
		word->refined_word = word_content;
	return (false);
}

bool	t_pipe_variable_handler(t_mini *mini, t_pipe *pipe)
{
	t_word	*current;

	current = pipe->words;
	while (current)
	{
		if (t_word_variable_handler(mini, current))
			return (true);
		current = current->next;
	}
	return (false);
}
