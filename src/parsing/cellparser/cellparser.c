/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/06/05 18:08:01 by marvin            #+#    #+#             */
/*   Updated: 2024/06/05 18:08:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/all.h>

bool	split_t_char_list(t_mini *mini, t_pipe *pipe, ssize_t pipe_pos)
{
	char *raw_words;
	char **words;
	ssize_t index;

	raw_words = NULL;
	words = NULL;
	index = -1;
	pipe->pos = pipe_pos;
	raw_words = string_constructor(mini, pipe->raw_words);
	words = mini->libft->split(mini->solib, raw_words, ' ');
	mini->free(mini, raw_words);
	while(words[++index])
	{
		if (words[index][0] == '<')
			word_add_back(mini, &pipe->in_fd, words[index]);
		else if (words[index][0] == '>')
			word_add_back(mini, &pipe->ou_fd, words[index]);
		else
			word_add_back(mini, &pipe->words, words[index]);
	}
	print_t_pipe(mini, pipe);
	return (false);
}

bool	t_word_parse_cmd(t_mini *mini, t_word *word)
{
	word->refined_word = string_constructor(mini, word->c);
	return (false);
}

bool	t_word_parse_type(t_mini *mini, t_word *word)
{
	if (t_word_parse_cmd(mini, word))
		return (false);
	return (true);
}

bool	cellparser_parser(t_mini *mini, t_cell *cell)
{
	ssize_t index;

	index = -1;
	while (++index < cell->nb_pipes)
		if (split_t_char_list(mini, &cell->pipes[index], index))
			return (true);
	return (false);
}
