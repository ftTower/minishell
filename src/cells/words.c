/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 02:19:45 by tauer             #+#    #+#             */
/*   Updated: 2024/07/04 01:48:50 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/all.h>

bool	word_add_back(t_mini *mini, t_word **words_list, char *word)
{
	ssize_t	index;
	t_word	*new;
	t_word	*current;

	new = mini->malloc(mini, sizeof(t_word));
	new->c = NULL;
	new->next = NULL;
	new->type = ERROR_TYPE;
	index = -1;
	while (word[++index])
		char_add_back(mini, new, word[index]);
	if (!(*words_list))
		*words_list = new;
	else
	{
		current = *words_list;
		while (current->next)
			current = current->next;
		current->next = new;
	}
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
