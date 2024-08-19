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
		|| cell_translator(mini, cell))
		return (t_history_add_line(mini, raw_line, false, cell));
	return (t_history_add_line(mini, raw_line, true, cell), print_t_cell(mini, cell));
}

bool	mini_parsing(t_mini *mini, char *line)
{
	char **cells;
	ssize_t index;
	DIR *dir;
	char cwd[1024];

	if (line && *line)
	{
		dir = opendir(line);
		if (dir && chdir(line) == 0)
		{
			replace_envpl_var(mini, "PWD=" , getcwd(cwd, sizeof(cwd)));
			closedir(dir);
    	}	
		else {
        perror("chdir");
		closedir(dir); // Print the error
   		}

		if (cells_empty_char(line, ';'))
			return (handle_error(mini, line, ERROR_EMPTY_SEMICOLON),true);
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
