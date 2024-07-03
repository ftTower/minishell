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

bool	fd_getter(t_mini *mini, t_char *current, t_pipe *pipe)
{
	t_char *word_rest;

	word_rest = current->next;
	printf("fd getter\n");
	while (word_rest)
	{
		print_t_char(mini, word_rest, RED);
		word_rest = word_rest->next;
	}
	mini->print("%d\n", pipe->pos);
	return (false);
}

bool	fd_watcher(t_mini *mini, t_word *word, t_pipe *pipe)
{
	t_char *current;

	current = word->c;
	while (current)
	{
		if (((current->next && (current->next->c == '<'
						|| current->next->c == '>')) || (current->pos == 0
					&& (current->c == '<' || current->c == '>')))
			&& fd_getter(mini, current, pipe))
			return (true);
		current = current->next;
	}
	printf("\n");
	return (false);
}

bool	word_char_indexer(t_word *word)
{
	t_char *current;
	ssize_t pos;

	pos = 0;
	current = word->c;
	if (!word || !word->c)
		return (true);
	while (current)
	{
		current->pos = pos++;
		current = current->next;
	}
	return (false);
}

bool	word_parser(t_mini *mini, t_pipe *pipe, t_word *word, ssize_t word_pos)
{
	word->pos = word_pos;
	if (word_char_indexer(word))
		return (true);
	while (fd_watcher(mini, word, pipe))
		write(1, "", 0);
	return (false);
}

bool	pipe_parser(t_mini *mini, t_pipe *pipe, ssize_t pipe_pos)
{
	t_word *current;
	ssize_t word_pos;

	current = pipe->words;
	pipe->pos = pipe_pos;
	word_pos = 0;
	while (current)
	{
		if (word_parser(mini, pipe, current, word_pos++))
			return (true);
		current = current->next;
	}

	// print_t_pipe(mini, pipe);
	return (false);
}

bool	cell_parser(t_mini *mini, t_cell *cell)
{
	ssize_t index;

	index = -1;
	while (++index < cell->nb_pipes)
		if (pipe_parser(mini, &cell->pipes[index], index))
			return (true);
	return (false);
}

bool	cell_maker(t_mini *mini, t_cell *cell, char *raw_line)
{
	ssize_t size;

	if (!raw_line || !*raw_line || cells_empty_pipe(mini, raw_line))
		return (mini->print("returned in cells liner\n"), true);
	cell->lines = mini->libft->split(mini->solib, raw_line, '|');
	if (strtlen(cell->lines, &size))
		return (true);
	cell->nb_pipes = size;
	cell->pipes = mini->malloc(mini, sizeof(t_pipe) * size);
	size = -1;
	while (cell->lines[++size])
		if (pipe_maker(mini, &cell->pipes[size], mini->libft->split(mini->solib,
					cell->lines[size], ' ')))
			return (true);
	return (mini->print("\n[cell no : %d][%d pipes]\n", cell->pos,
			cell->nb_pipes), false);
}

// contient une seul cell ; ...|...|... ;

bool	cells_handler(t_mini *mini, char *raw_line, size_t pos)
{
	t_cell *cell;

	mini->print("\n[line] > %s\n", raw_line);
	cell = mini->malloc(mini, sizeof(t_cell));
	cell->pos = pos;
	if (cell_maker(mini, cell, raw_line) || cell_parser(mini, cell))
		return (true);
	return (false);
}
