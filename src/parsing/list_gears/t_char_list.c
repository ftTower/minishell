/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_char_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/07/09 01:43:38 by tauer             #+#    #+#             */
/*   Updated: 2024/08/17 00:38:24 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/all.h>
#include <stdbool.h>

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

t_char	*t_char_new(t_mini *mini, char c)
{
	t_char	*new;

	new = mini->malloc(mini, sizeof(t_char));
	new->c = c;
	new->type_quotes = TYPEQUOTES_UNSET;
	new->next = NULL;
	return (new);
}

bool	t_char_add_pos(t_mini *mini, t_char **dst, size_t pos, char c)
{
	t_char	*new;
	t_char	*current;
	t_char	*previous;

	new = t_char_new(mini, c);
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

bool	t_char_del_pos(t_mini *mini, t_char **list, size_t pos_to_del)
{
	t_char	*current;
	t_char	*tmp;

	if (pos_to_del == 0)
		return (*list = (*list)->next, t_char_set_pos(*list), false);
	t_char_set_pos(*list);
	current = (*list);
	while (current)
	{
		if (current->next && current->next->pos == pos_to_del)
			return (tmp = current->next, current->next = tmp->next,
				mini->free(mini, tmp), tmp = NULL, t_char_set_pos(*list),
				false);
		current = current->next;
	}
	return (false);
}
