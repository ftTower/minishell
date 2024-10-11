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

void	t_pipex_fill_in_fd(t_mini *mini, t_cell *cell, t_pipex *ret,
		ssize_t index)
{
	if (!ret->in_fd && (t_word_list_has_type(cell->pipes[index].fds,
				REPLACE_IN_FD_TYPE)))
		ret->in_fd = t_word_to_str(mini,
				t_word_list_get_type(&cell->pipes[index].fds,
					REPLACE_IN_FD_TYPE));
	else if (!ret->in_fd && (t_word_list_has_type(cell->pipes[index].fds,
				CONCATE_IN_FD_TYPE)))
		ret->in_fd = t_word_to_str(mini,
				t_word_list_get_type(&cell->pipes[index].fds,
					CONCATE_IN_FD_TYPE));
}

bool	t_pipex_fill_out_ft(t_mini *mini, t_cell *cell, t_pipex *ret,
		ssize_t index)
{
	if (!ret->out_fd && (t_word_list_has_type(cell->pipes[index].fds,
				REPLACE_OUT_FD_TYPE)))
		return (ret->out_fd = t_word_to_str(mini,
				t_word_list_get_type(&cell->pipes[index].fds,
					REPLACE_OUT_FD_TYPE)), true);
	else if (!ret->out_fd && (t_word_list_has_type(cell->pipes[index].fds,
				CONCATE_OUT_FD_TYPE)))
		return (ret->out_fd = t_word_to_str(mini,
				t_word_list_get_type(&cell->pipes[index].fds,
					CONCATE_OUT_FD_TYPE)));
	return (false);
}

t_pipex	*t_pipex_fill(t_mini *mini, t_cell *cell, t_pipex *ret)
{
	char	*tmp;
	t_word	*cmd_line;
	ssize_t	index;

	index = -1;
	cmd_line = NULL;
	while (++index < cell->nb_pipes)
	{
		if (!cell->pipes[index].used)
		{
			cell->pipes[index].used = true;
			t_pipex_fill_in_fd(mini, cell, ret, index);
			t_word_list_add_back(mini, &cmd_line, cell->pipes[index].words);
			if (t_pipex_fill_out_ft(mini, cell, ret, index))
				break ;
			else
				word_add_back(mini, &cmd_line, ";");
		}
	}
	if (!ret->in_fd)
		ret->in_fd = "/dev/stdin";
	if (!ret->out_fd)
		ret->out_fd = "/dev/stdout";
	return (tmp = t_word_list_to_str(mini, cmd_line),
		ret->args = mini->libft->split(mini->solib, tmp, ';'), ret);
}

bool	is_unused_t_pipe_in_cell(t_cell *cell)
{
	ssize_t	index;

	index = -1;
	while (++index < cell->nb_pipes)
	{
		if (!cell->pipes[index].used)
			return (true);
	}
	return (false);
}

bool	cell_translator(t_mini *mini, t_cell *cell)
{
	cell->final_line = NULL;
	while (is_unused_t_pipe_in_cell(cell))
		t_pipex_add_back(&cell->final_line, t_pipex_fill(mini, cell,
				new_t_pipex(mini)));
	return (false);
}
