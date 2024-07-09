/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_char_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 01:43:38 by tauer             #+#    #+#             */
/*   Updated: 2024/07/09 02:10:44 by tauer            ###   ########.fr       */
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

bool	strr_to_t_char_list(t_mini *mini, t_char **dst, char **src)
{
	ssize_t index;
	ssize_t char_index;

	index = -1;
	while (src[++index])
	{
		char_index = -1;
		while (src[index][++char_index])
		{
			if ((src[index][char_index] == '<' || src[index][char_index] == '>')
				&& (char_index > 0 && (src[index][char_index - 1] != '<'
						&& src[index][char_index - 1] != '>')))
				char_t_char_add_back(mini, dst, ' ');
			char_t_char_add_back(mini, dst, src[index][char_index]);
		}
		char_t_char_add_back(mini, dst, ' ');
	}
	return (false);
}