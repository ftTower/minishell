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
#include <solibft/sostring.h>

void	cells_handler(t_mini *mini, char *raw_line, size_t pos)
{
	t_cell	*cell;

	cell = mini->malloc(mini, sizeof(t_cell));
	cell->pos = pos;
	if (cell_maker(mini, cell, raw_line) || cell_parser(mini, cell)
		|| cell_translator(mini, cell) || cell_pipex_exec(mini,
			cell->final_line))
		return ;
}

bool	is_raw_path(t_mini *mini, char *line)
{
	char	*path;
	char	*home;
	char	*pwd;

	home = get_envpl_var(mini, "HOME");
	if (!line || !*line || !ft_strcmp(line, "~"))
		path = home;
	else if (!ft_strncmp(line, "~/", 2))
		path = ft_strjoin(NULL, home, line + 1);
	else
		path = line;
	if (!chdir(path))
	{
		if (path != line && path != home)
			free(path);
		pwd = getcwd(NULL, 0);
		replace_envpl_var(mini, "PWD=", pwd);
		free(pwd);
		return (true);
	}
	if (path != line && path != home)
		free(path);
	return (handle_error(mini, path, ERROR_TYPE_DIRECTORY), false);
}

bool	mini_parsing(t_mini *mini, char *line)
{
	char	**cells;
	ssize_t	index;

	if (line && *line && !(!ft_strncmp("cd ", line, 3)
			&& is_raw_path(mini, line + 3)))
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
