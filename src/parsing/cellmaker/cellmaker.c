/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:08:01 by marvin            #+#    #+#             */
/*   Updated: 2024/06/05 18:08:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/all.h>

bool	cellmaker_pipe_maker(t_mini *mini, t_pipe *pipe, char **pipe_words, ssize_t pipe_pos)
{
	pipe->words = NULL;
	pipe->fds = NULL;
	pipe->raw_words = NULL;
	pipe->pos = pipe_pos;
	if (string_builder(mini, pipe, pipe_words))
		return (true);
	// mini->print("\n\t%Cff0000([)%Cf1c40f(PIPE)%Cff0000(]) > ");

	return (false);
}

bool	cellmaker_maker(t_mini *mini, t_cell *cell, char *raw_line)
{
	ssize_t size;

	if (!raw_line || !*raw_line || cells_empty_pipe(mini, raw_line))
		return (mini->print("returned in cells liner\n"), true);
	cell->lines = mini->libft->split(mini->solib, raw_line, '|');
	if (strtlen(cell->lines, &size))
		return (true);
	cell->nb_pipes = size;
	cell->pipes = mini->malloc(mini, sizeof(t_pipe) * size);
	size = -1;
	while (cell->lines[++size])
		if (cellmaker_pipe_maker(mini, &cell->pipes[size], mini->libft->split(mini->solib,
					cell->lines[size], ' '), size))
			return (true);
	return (false);
}

