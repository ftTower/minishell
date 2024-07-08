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


bool	split_t_char_list(t_mini *mini, t_pipe *pipe, ssize_t pipe_pos)
{
	char *raw_words;
	char **words;
	ssize_t index;

	raw_words = NULL;
	words = NULL;
	index = -1;
	pipe->pos = pipe_pos;
	raw_words = string_constructor(mini, pipe->raw_words);
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

void	free_tab(char **tab)
{
	ssize_t index;

	index = -1;
	while (tab[++index])
		free(tab[index]);
	free(tab);
}

bool	t_word_parse_cmd(t_mini *mini, t_word *word)
{
	char *path;
	char *current_path;
	char **parse_path;
	ssize_t index;

	path = get_envpl_var(mini, "PATH=");
	if (!path)
		return (false);
	parse_path = mini->libft->split(mini->solib, path, ':');
	index = -1;
	while (parse_path[++index])
	{
		current_path = mini->libft->strjoin(mini->solib,
				mini->libft->strjoin(mini->solib, parse_path[index], "/"),
				word->refined_word);
		if (!access(current_path, X_OK | F_OK))
			return (free_tab(parse_path), free(current_path),
				word->type = CMD_TYPE, true);
		free(current_path);
	}
	return (free_tab(parse_path), false);
}

bool	t_word_parse_redirect(t_word *word)
{
	if (!word->c || !word->c->next)
		return (false);
	else if (word->c->c == '<' && word->c->next->c == '<'
		&& word->c->next->next)
		return (word->type = CONCATE_IN_FD_TYPE, true);
	else if (word->c->c == '>' && word->c->next->c == '>'
		&& word->c->next->next)
		return (word->type = CONCATE_OUT_FD_TYPE, true);
	else if (word->c->c == '<')
		return (word->type = REPLACE_IN_FD_TYPE, true);
	else if (word->c->c == '>')
		return (word->type = REPLACE_OUT_FD_TYPE, true);
	return (false);
}

bool	t_word_parse_para(t_word *word)
{
	if (!word->c || word->c->c != '-' || !word->c->next)
		return (false);
	return (word->type = PARA_TYPE, true);
}

bool	t_word_parse_type(t_mini *mini, t_word *word)
{
	word->refined_word = string_constructor(mini, word->c);
	if (t_word_parse_para(word) || t_word_parse_redirect(word)
		|| t_word_parse_cmd(mini, word))
		return (false);
	return (word->type = ARG_TYPE, true);
}

bool	t_pipe_parse_type(t_mini *mini, t_pipe *pipe)
{
	t_word *current;

	current = pipe->words;
	while (current)
	{
		t_word_parse_type(mini, current);
		current = current->next;
	}
	current = pipe->fds;
	while (current)
	{
		t_word_parse_type(mini, current);
		current = current->next;
	}
	return (false);
}

bool	cellparser_parser(t_mini *mini, t_cell *cell)
{
	ssize_t index;

	index = -1;
	while (++index < cell->nb_pipes)
		if (split_t_char_list(mini, &cell->pipes[index], index)
			|| t_pipe_parse_type(mini, &cell->pipes[index]))
			return (true);
	return (false);
}
