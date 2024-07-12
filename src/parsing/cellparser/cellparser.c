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

bool	t_pipe_organizer(t_mini *mini, t_pipe *pipe, ssize_t pipe_pos)
{
	char *raw_words;
	char **words;
	ssize_t index;

	raw_words = NULL;
	words = NULL;
	index = -1;
	pipe->pos = pipe_pos;
	raw_words = t_char_list_to_str(mini, pipe->raw_words);
	words = mini->libft->split(mini->solib, raw_words, ' ');
	mini->free(mini, raw_words);
	while (words[++index])
	{
		if (words[index][0] == '<' || words[index][0] == '>')
			word_add_back(mini, &pipe->fds, words[index]);
		else
			word_add_back(mini, &pipe->words, words[index]);
	}
	return (false);
}

bool	delete_word_in_list(t_mini *mini, t_word **words_list, t_word *word)
{
	t_word *current;
	t_word *previous;

	current = *words_list;
	previous = NULL;
	while (current)
	{
		if (current == word)
		{
			if (previous)
				previous->next = current->next;
			else
				*words_list = current->next;
			mini->free(mini, current);
			return (true);
		}
		previous = current;
		current = current->next;
	}
	return (false);
}

bool	open_fd(t_mini *mini, t_word *word)
{
	int fd;

	if (word->type == REPLACE_IN_FD_TYPE || word->type == REPLACE_OUT_FD_TYPE)
		word->refined_word = t_char_list_to_str(mini, word->c->next);
	else if (word->type == CONCATE_IN_FD_TYPE || word->type == CONCATE_OUT_FD_TYPE)
		word->refined_word = t_char_list_to_str(mini, word->c->next->next);
	else
		return (mini->print("wrong type in open_fd\n"),false);
	if (word->type == REPLACE_IN_FD_TYPE || word->type == CONCATE_IN_FD_TYPE)
	{
		fd = open(word->refined_word, O_RDONLY);
		if (fd == -1)
			return (mini->print("failed to open [in] : [%s]\n", word->refined_word),true);
		close(fd);
	}
	else if (word->type == REPLACE_OUT_FD_TYPE || word->type == CONCATE_OUT_FD_TYPE)
	{
		fd = open(word->refined_word, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			return (mini->print("failed to open [out] : [%s]\n", word->refined_word),true);
		close(fd);
	}
	return (false);
}

bool	fd_parser(t_mini *mini, t_word **dst)
{
	t_word *current;
	t_word *next;

	current = *dst;
	while(current)
	{
		next = current->next;
		if ((current->type == REPLACE_IN_FD_TYPE || current->type == CONCATE_IN_FD_TYPE) && (t_word_list_has_type(current->next, REPLACE_IN_FD_TYPE) || t_word_list_has_type(current->next, CONCATE_IN_FD_TYPE)))
		{
				if (open_fd(mini, current))
					return (true);
				delete_word_in_list(mini, dst, current);
		}
		else if ((current->type == REPLACE_OUT_FD_TYPE || current->type == CONCATE_OUT_FD_TYPE) && (t_word_list_has_type(current->next, REPLACE_OUT_FD_TYPE) || t_word_list_has_type(current->next, CONCATE_OUT_FD_TYPE)))
		{
				if (open_fd(mini, current))
					return (true);
				delete_word_in_list(mini, dst, current);
		}
		current = next;
	}
	return (false);
}

bool	t_cell_connect_fd(t_mini *mini, t_cell *cell)
{
	ssize_t index;

	index = -1;
	while(++index + 1 < cell->nb_pipes)
	{
		if (!t_word_list_has_type(cell->pipes[index].fds, REPLACE_OUT_FD_TYPE) && !t_word_list_has_type(cell->pipes[index].fds, CONCATE_OUT_FD_TYPE) && (t_word_list_has_type(cell->pipes[index + 1].fds, REPLACE_IN_FD_TYPE) || t_word_list_has_type(cell->pipes[index + 1].fds, CONCATE_IN_FD_TYPE)))
			word_add_back(mini, &cell->pipes[index].fds, ">/dev/null");
		else if ((t_word_list_has_type(cell->pipes[index].fds, REPLACE_OUT_FD_TYPE) || t_word_list_has_type(cell->pipes[index].fds, CONCATE_OUT_FD_TYPE)) && (!t_word_list_has_type(cell->pipes[index + 1].fds, REPLACE_IN_FD_TYPE) && !t_word_list_has_type(cell->pipes[index + 1].fds, CONCATE_IN_FD_TYPE)))
			word_add_back(mini, &cell->pipes[index + 1].fds, "</dev/null");
	}
	return (false);
}

bool	cell_parser(t_mini *mini, t_cell *cell)
{
	ssize_t index;

	index = -1;
	while (++index < cell->nb_pipes)
		if (t_pipe_organizer(mini, &cell->pipes[index], index)|| t_cell_connect_fd(mini, cell) || fd_parser(mini, &cell->pipes[index].fds))
			return (true);
	return (false);
}
