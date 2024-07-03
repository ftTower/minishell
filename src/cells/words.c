/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 02:19:45 by tauer             #+#    #+#             */
/*   Updated: 2024/07/03 02:37:21 by tauer            ###   ########.fr       */
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
