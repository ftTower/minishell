/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringbuilder_t_word.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:35:32 by tauer             #+#    #+#             */
/*   Updated: 2024/07/05 15:36:01 by tauer            ###   ########.fr       */
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
