/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_char_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 01:43:38 by tauer             #+#    #+#             */
/*   Updated: 2024/07/26 22:34:40 by tauer            ###   ########.fr       */
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
	ssize_t	index;
	ssize_t	char_index;

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

void	t_char_set_pos(t_char *list)
{
	ssize_t	index;

	index = 0;
	while (list)
	{
		list->pos = index++;
		list = list->next;
	}
}

bool	t_char_del_pos(t_char **dst, size_t pos)
{
	t_char	*current;
	t_char	*previous;

	t_char_set_pos((*dst));
	current = (*dst);
	previous = NULL;
	while (current)
	{
		if (current->pos == pos)
		{
			if (previous)
				previous->next = current->next;
			else
				(*dst) = current->next;
			t_char_set_pos((*dst));
			return (false);
		}
		previous = current;
		current = current->next;
	}
	return (true);
}

bool	t_char_add_pos(t_mini *mini, t_char **dst, size_t pos, char c)
{
	t_char	*new;
	t_char	*current;
	t_char	*previous;

	new = mini->malloc(mini, sizeof(t_char));
	new->c = c;
	new->next = NULL;
	t_char_set_pos((*dst));
	current = (*dst);
	previous = NULL;
	while (current)
	{
		if (current->pos == pos)
		{
			if (previous)
				previous->next = new;
			else
				(*dst) = new;
			new->next = current;
			t_char_set_pos((*dst));
			return (false);
		}
		previous = current;
		current = current->next;
	}
	return (true);
}
