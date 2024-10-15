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
	if (!pipe_words || !*pipe_words || mini_formater(mini, pipe, pipe_words))
		return (true);
	return (false);
}

void	patern_negative_char(char current, bool double_quotes, \
bool single_quotes, bool false_it)
{
	if (double_quotes || single_quotes)
	{
		if (current == ' ' && false_it)
			current = '\x01';
		else if (current == '\x01' && !false_it)
			current = ' ';
		else if (current == '|' && false_it)
			current = '\x02';
		else if (current == '\x02' && !false_it)
			current = '|';
		else if (current == '<' && false_it)
			current = '\x03';
		else if (current == '\x03' && !false_it)
			current = '<';
		else if (current == '>' && false_it)
			current = '\x04';
		else if (current == '\x04' && false_it)
			current = '>';
	}
}

void	handle_negative_char_in_quotes(char *line, bool false_it)
{
	ssize_t	index;
	bool	double_quotes;
	bool	single_quotes;

	double_quotes = false;
	single_quotes = false;
	index = -1;
	while (line[++index])
	{
		char_bool_quotes_switcher(line[index], &single_quotes, &double_quotes);
		patern_negative_char(line[index], \
		double_quotes, single_quotes, false_it);
	}
}

char	**cell_split(t_mini *mini, char *line_dup)
{
	char	**ret;

	handle_negative_char_in_quotes(line_dup, true);
	if (!line_dup || !*line_dup || \
	cells_empty_char(line_dup, '|'))
		return (handle_error(mini, line_dup, \
		ERROR_EMPTY_PIPE), free(line_dup), NULL);
	ret = mini->libft->split(mini->solib, line_dup, '|');
	return (ret);
}

bool	cell_maker(t_mini *mini, t_cell *cell, char *raw_line)
{
	ssize_t	size;
	char	**lines;
	char	*transformed_line;

	transformed_line = mini->libft->strdup(NULL, raw_line);
	lines = cell_split(mini, raw_line);
	if (strtlen(lines, &size))
		return (free(transformed_line), true);
	cell->nb_pipes = size;
	cell->final_line = NULL;
	cell->pipes = mini->malloc(mini, sizeof(t_pipe) * size);
	if (!cell->pipes)
		return (free(transformed_line), true);
	size = -1;
	while (lines[++size])
	{
		handle_negative_char_in_quotes(transformed_line, false);
		if (cell_pipe_maker(mini, &cell->pipes[size],
				mini->libft->split(mini->solib, lines[size], ' '), size))
			return (free(transformed_line), true);
	}
	return (free(transformed_line), false);
}
