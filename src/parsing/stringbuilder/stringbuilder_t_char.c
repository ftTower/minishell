/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringbuilder_t_char.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:35:40 by tauer             #+#    #+#             */
/*   Updated: 2024/07/05 15:35:42 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/all.h>

bool	char_add_back(t_mini *mini, t_word *word, char c)
{
	t_char	*new;
	t_char	*current;

	new = mini->malloc(mini, sizeof(t_char));
	new->c = c;
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
	new->next = NULL;
	if (!(*list) || !(*list)->c)
		return ((*list) = new, false);
	current = (*list);
	while (current->next)
		current = current->next;
	return (current->next = new, false);
}

bool	char_t_char_del_pos(t_mini *mini, t_char **list, ssize_t pos)
{
	t_char	*current;
	t_char	*tmp;
	ssize_t	index;

	if (!(*list) || pos < 0)
		return (false);
	if (pos == 0)
	{
		tmp = (*list);
		(*list) = (*list)->next;
		mini->free(mini, tmp);
		return (true);
	}
	index = 0;
	current = (*list);
	while (current->next && ++index < pos)
		current = current->next;
	if (!current->next)
		return (false);
	tmp = current->next;
	current->next = current->next->next;
	mini->free(mini, tmp);
	return (true);
}