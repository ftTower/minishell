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

void	cells_handler(t_mini *mini, char *raw_line, size_t pos)
{
	t_cell *cell;
	cell = mini->malloc(mini, sizeof(t_cell));
	cell->pos = pos;
	if (cell_maker(mini, cell, raw_line) || cell_parser(mini, cell)
		|| cell_translator(mini, cell) || cell_pipex_exec(mini, cell->final_line))
		return (t_history_add_line(mini, raw_line, false, cell));
	return (t_history_add_line(mini, raw_line, true, cell), print_t_cell(mini, cell));
}

bool	is_raw_path(t_mini *mini, char *line)
{
	DIR *dir;
	char cwd[1024];
	dir = opendir(line);
		
	if (dir && chdir(line) == 0)
		return (replace_envpl_var(mini, "PWD=" , getcwd(cwd, sizeof(cwd))), closedir(dir), true);	
	closedir(dir);
	return (false);
}

bool	mini_parsing(t_mini *mini, char *line)
{
	char **cells;
	ssize_t index;

	if (line && *line && !is_raw_path(mini, line))
	{
		// pwd(mini, 0);
		// echon( "pas de ln", 0);
		// unset(mini, "PWD", 0);
		if (cells_empty_char(line, ';'))
			return (handle_error(mini, line, ERROR_EMPTY_SEMICOLON),t_history_add_line(mini, line, false, NULL), true);
		mini->print("\n");
		cells = mini->libft->split(mini->solib, line, ';');
		index = -1;
		while (cells[++index])
			cells_handler(mini, cells[index], index);
	}
	else
		return (true);
	return (false);
}
