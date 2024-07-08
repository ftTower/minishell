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
// contient une seul cell ; ...|...|... ;

bool	cells_handler(t_mini *mini, char *raw_line, size_t pos)
{
	t_cell *cell;

	cell = mini->malloc(mini, sizeof(t_cell));
	cell->pos = pos;
	if (cellmaker_maker(mini, cell, raw_line) || cellparser_parser(mini, cell)
		|| celltranslator_translator(mini, cell))
		return (true);
	return (false);
}

bool	mini_parsing(t_mini *mini, char *line)
{
	char **cells;
	ssize_t index;

	if (line && *line)
	{
		mini->print("\n");
		cells = mini->libft->split(mini->solib, line, ';');
		index = -1;
		while (cells[++index])
			if (cells_handler(mini, cells[index], index))
				break ;
		// mini->print("\nParser stoppped at [cell no %d]\n", index - 1);
	}
	return (false);
}
