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

void	cells_handler(t_mini *mini, char *raw_line, size_t pos)
{
	t_cell	*cell;

	cell = mini->malloc(mini, sizeof(t_cell));
	cell->pos = pos;
	if (cell_maker(mini, cell, raw_line) || cell_parser(mini, cell)
		|| cell_translator(mini, cell) || cell_pipex_exec(mini,
			cell->final_line))
		return ;
	//print_t_cell(mini, cell);
}

bool	is_raw_path(t_mini *mini, char *line)
{
	DIR	*dir;

	dir = opendir(line);
	if (dir && chdir(line) == 0)
		return (handle_error(mini, line, ERROR_TYPE_DIRECTORY), true);
	closedir(dir);
	return (false);
}

bool	mini_parsing(t_mini *mini, char *line)
{
	char	**cells;
	ssize_t	index;

	if (line && *line && !is_raw_path(mini, line))
	{
		if (cells_empty_char(line, ';'))
			return (handle_error(mini, line, ERROR_EMPTY_SEMICOLON), true);
		cells = mini->libft->split(mini->solib, line, ';');
		index = -1;
		while (cells[++index])
			cells_handler(mini, cells[index], index);
	}
	else
		return (true);
	return (false);
}
