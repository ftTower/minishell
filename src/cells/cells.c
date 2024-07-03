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


// typedef struct s_cell
// {
// 	char **lines;
// 	t_pipe *pipes;

// } t_cell;

//  echo start > outfile ; ls | cat -e | wc -l ; echo finished

bool	cell_maker(t_mini *mini, t_cell *cell, char *raw_line)
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
		if (pipe_maker(mini, &cell->pipes[size], mini->libft->split(mini->solib,
					cell->lines[size], ' ')))
			return (true);
	return (mini->print("[cell no : %d][%d pipes]\n", cell->pos,
			cell->nb_pipes), false);
}

// contient une seul cell ; ...|...|... ;

bool	cells_handler(t_mini *mini, char *raw_line, size_t pos)
{
	t_cell *cell;

	mini->print("\n[line] > %s\n", raw_line);
	cell = mini->malloc(mini, sizeof(t_cell));
	cell->pos = pos;
	if (cell_maker(mini, cell, raw_line))
		return (true);
	return (false);
}
