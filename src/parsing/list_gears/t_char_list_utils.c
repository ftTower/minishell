/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_char_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 21:07:04 by tauer             #+#    #+#             */
/*   Updated: 2024/10/11 21:37:14 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/all.h>

bool	char_add_back(t_mini *mini, t_word *word, char c)
{
	t_char	*new;
	t_char	*current;

	new = mini->malloc(mini, sizeof(t_char));
	new->c = c;
	new->type_quotes = TYPEQUOTES_UNSET;
	new->next = NULL;
	if (!word || !word->c)
		return (word->c = new);
	current = word->c;
	while (current->next)
		current = current->next;
	return (current->next = new, false);
}

bool	char_t_char_add_back(t_mini *mini, t_char **list, char c)
{
	t_char	*new;
	t_char	*current;

	new = mini->malloc(mini, sizeof(t_char));
	new->c = c;
	new->type_quotes = TYPEQUOTES_UNSET;
	new->next = NULL;
	if (!(*list) || !(*list)->c)
		return ((*list) = new, false);
	current = (*list);
	while (current->next)
		current = current->next;
	return (current->next = new, false);
}
