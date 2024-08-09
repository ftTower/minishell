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


bool	cell_pipe_maker(t_mini *mini, t_pipe *pipe, char **pipe_words,
		ssize_t pipe_pos)
{
	pipe->words = NULL;
	pipe->fds = NULL;
	pipe->raw_words = NULL;
	pipe->used = false;
	pipe->pos = pipe_pos;
	pipe->error_list = NULL;
	if (!pipe_words || !*pipe_words || mini_formater(mini, pipe, pipe_words))
		return (add_error_to_list(mini, &pipe->error_list,
				ERROR_CHECKPOINT_CELL_PIPE_MAKER, NULL),  true);
	return (false);
}

bool	is_quoted(char *str, ssize_t index)
{
	ssize_t start;

	start = index;
	while (start > 0 && str[start] != '"')
		--start;
	while (str[++index])
		if (str[start] == '"' && str[index] == '"')
			return (true);
	return (false);
}

char	*preserve_space_in_quote(t_mini *mini, char *str_to_dup)
{
	ssize_t index;
	char *dup;

	index = -1;
	dup = mini->malloc(mini, sizeof(char) * (mini->libft->strlen(str_to_dup)
				+ 1));
	while (str_to_dup[++index])
	{
		if (str_to_dup[index] == ' ' && is_quoted(str_to_dup, index))
			dup[index] = '|';
		else
			dup[index] = str_to_dup[index];
	}
	return (dup[index] = '\0', dup);
}

bool	cell_maker(t_mini *mini, t_cell *cell, char *raw_line)
{
	ssize_t size;
	char **lines;

	if (!raw_line || !*raw_line || cells_empty_char(mini, raw_line, '|'))
		return (add_error_to_list(mini, &cell->error_list, ERROR_EMPTY_PIPE,
				raw_line), true);
	lines = mini->libft->split(mini->solib, raw_line, '|');
	if (strtlen(lines, &size))
		return (true);
	cell->nb_pipes = size;
	cell->final_line = NULL;
	cell->pipes = mini->malloc(mini, sizeof(t_pipe) * size);
	size = -1;
	while (lines[++size])
		if (cell_pipe_maker(mini, &cell->pipes[size],
				mini->libft->split(mini->solib, preserve_space_in_quote(mini,
						lines[size]), ' '), size))
			t_error_cpy(mini, &cell->error_list, cell->pipes[size].error_list);
	return (false);
}
