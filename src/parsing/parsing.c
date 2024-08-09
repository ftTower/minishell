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

bool	cells_handler(t_mini *mini, t_error_list *error_list ,char *raw_line, size_t pos)
{
	t_cell *cell;

	cell = mini->malloc(mini, sizeof(t_cell));
	cell->pos = pos;
	cell->error_list = NULL;
	error_list = NULL;
	if (cell_maker(mini, cell, raw_line) || cell_parser(mini, cell)
		|| cell_translator(mini, cell))
		return (print_error_list(mini, cell->error_list), true);
	return (print_t_cell(mini, cell), print_error_list(mini, cell->error_list), false);
}

bool	mini_parsing(t_mini *mini, char *line)
{
	char **cells;
	ssize_t index;
	t_error_list *error_list;

	error_list = NULL;
	if (line && *line)
	{
		if (cells_empty_char(mini, line, ';'))
			return (add_error_to_list(mini, &error_list, ERROR_EMPTY_SEMICOLON, line), true);
		mini->print("\n");
		cells = mini->libft->split(mini->solib, line, ';');
		index = -1;
		while (cells[++index])
			cells_handler(mini, error_list ,cells[index], index);
	}
	else
		return (true);
	return (false);
}
