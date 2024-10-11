/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_word_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
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

bool	t_word_list_add_back(t_mini *mini, t_word **dst, t_word *src)
{
	t_word	*current;

	current = src;
	while (current)
	{
		word_add_back(mini, dst, current->refined_word);
		if (current->next)
			word_add_back(mini, dst, " ");
		current = current->next;
	}
	return (false);
}

bool	delete_word_in_list(t_mini *mini, t_word **words_list, t_word *word)
{
	t_word	*current;
	t_word	*previous;

	current = *words_list;
	previous = NULL;
	while (current)
	{
		if (current == word)
		{
			if (previous)
				previous->next = current->next;
			else
				*words_list = current->next;
			mini->free(mini, current);
			return (true);
		}
		previous = current;
		current = current->next;
	}
	return (false);
}

bool	t_word_list_has_type(t_word *words, t_type type)
{
	t_word	*current;

	current = words;
	while (current)
	{
		if (current->type == type)
			return (true);
		current = current->next;
	}
	return (false);
}

t_word	*t_word_list_get_type(t_word **dst, t_type to_get)
{
	t_word	*current;
	t_word	*ret;

	current = *dst;
	ret = NULL;
	while (current)
	{
		if (current->type == to_get)
		{
			ret = current;
			break ;
		}
		current = current->next;
	}
	return (ret);
}
