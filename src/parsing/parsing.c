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
	if (cell_maker(mini, cell, raw_line) || cell_parser(mini, cell)
		|| cell_translator(mini, cell))
		return (true);
	return (print_t_cell(mini, cell), false);
}

bool	mini_parsing(t_mini *mini, char *line)
{
	char **cells;
	ssize_t index;

	if (line && *line && !cells_empty_char(mini, line, ';'))
	{
		mini->print("\n");
		cells = mini->libft->split(mini->solib, line, ';');
		index = -1;
		while (cells[++index])
			if (cells_handler(mini, cells[index], index))
				break ;
			//add a error_catcher
		// mini->print("\nParser stoppped at [cell no %d]\n", index - 1);
	}
	return (false);
}
