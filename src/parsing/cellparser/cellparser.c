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

bool	t_pipe_organizer(t_mini *mini, t_pipe *pipe, ssize_t pipe_pos)
{
	char *raw_words;
	char **words;
	ssize_t index;

	raw_words = NULL;
	words = NULL;
	index = -1;
	pipe->pos = pipe_pos;
	raw_words = t_char_list_to_str(mini, pipe->raw_words);
	words = mini->libft->split(mini->solib, raw_words, ' ');
	mini->free(mini, raw_words);
	while (words[++index])
	{
		if (words[index][0] == '<' || words[index][0] == '>')
			word_add_back(mini, &pipe->fds, words[index]);
		else
			word_add_back(mini, &pipe->words, words[index]);
	}
	return (false);
}

bool	cell_parser(t_mini *mini, t_cell *cell)
{
	ssize_t index;

	index = -1;
	while (++index < cell->nb_pipes)
		if (t_pipe_organizer(mini, &cell->pipes[index], index))
			return (true);
	return (false);
}
