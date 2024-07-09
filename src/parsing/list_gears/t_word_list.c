/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_word_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 01:42:00 by tauer             #+#    #+#             */
/*   Updated: 2024/07/09 01:42:41 by tauer            ###   ########.fr       */
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
	new->refined_word = word;
	index = -1;
	while (word[++index])
		char_add_back(mini, new, word[index]);
	t_word_parse_type(mini, new);
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

bool	word_copy_back(t_mini *mini,t_word **words_list, t_word *word)
{
	t_word	*current;
	t_word 	*new;

	if (!word)
		return (true);
	new = mini->malloc(mini, sizeof(t_word));
	new->c = word->c;
	new->pos = word->pos;
	new->refined_word = word->refined_word;
	new->type = word->type;
	if (!(*words_list))
		*words_list = new;
	else
	{
		current = *words_list;
		while (current && current->next)
			current = current->next;
		current->next = new;
	}
	return (false);
}
