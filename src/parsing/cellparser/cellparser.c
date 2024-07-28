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


bool	t_pipe_parser(t_mini *mini, t_pipe *pipe, ssize_t pipe_pos)
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

char *t_word_get_variable(t_mini *mini, char *splitted)
{
	char *content;

	content = get_envpl_var(mini, splitted);
	// mini->print("%s -> %s\n",splitted, content);
	return (content);
}

bool	t_word_variable_handler(t_mini *mini, t_word *word)
{
	char **splitted;
	char *word_content;
	ssize_t index;

	if(word->refined_word[0] == '$' && !get_envpl_var(mini, word->refined_word + 1))
		return (word->refined_word = "",false);
	splitted = mini->libft->split(mini->solib, word->refined_word, '$');
	word_content = "";
	index = -1;
	while(splitted[++index])
	{
		if (t_word_get_variable(mini, splitted[index]))	
			mini->libft->strmcat(mini->solib, &word_content, t_word_get_variable(mini, splitted[index]));
		else if (index == 0)
			mini->libft->strmcat(mini->solib, &word_content, splitted[index]);
	}
	if (word_content && *word_content)
		word->refined_word = word_content;
	// mini->print("word_content: %s\n", word_content);
	return (false);
}

bool	t_pipe_variable_handler(t_mini *mini, t_pipe *pipe)
{
	t_word *current;

	current = pipe->words;
	while(current)
	{
		t_word_variable_handler(mini, current);
		current = current->next;
	}
	return (false);
}

bool	cell_parser(t_mini *mini, t_cell *cell)
{
	ssize_t index;

	index = -1;
	while (++index < cell->nb_pipes)
		if (t_pipe_parser(mini, &cell->pipes[index], index)
			|| t_cell_connect_fd(mini, cell) || fd_parser(mini,
				&cell->pipes[index].fds) || t_pipe_variable_handler(mini,
					&cell->pipes[index]))
			return (true);
	return (false);
}
