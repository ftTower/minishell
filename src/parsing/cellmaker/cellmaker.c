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

bool	cell_pipe_maker(t_mini *mini, t_pipe *pipe, char **pipe_words,
		ssize_t pipe_pos)
{
	pipe->words = NULL;
	pipe->fds = NULL;
	pipe->raw_words = NULL;
	pipe->pos = pipe_pos;
	if (mini_formater(mini, pipe, pipe_words))
		return (true);
	return (false);
}

bool	cell_maker(t_mini *mini, t_cell *cell, char *raw_line)
{
	ssize_t size;
	char **lines;

	if (!raw_line || !*raw_line || cells_empty_char(mini, raw_line, '|'))
		return (mini->print("returned in cells liner\n"), true);
	lines = mini->libft->split(mini->solib, raw_line, '|');
	if (strtlen(lines, &size))
		return (true);
	cell->nb_pipes = size;
	cell->pipes = mini->malloc(mini, sizeof(t_pipe) * size);
	size = -1;
	while (lines[++size])
		if (cell_pipe_maker(mini, &cell->pipes[size],
				mini->libft->split(mini->solib, lines[size], ' '), size))
			return (true);
	return (false);
}
