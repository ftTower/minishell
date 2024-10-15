/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_gears.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/07/05 15:20:46 by tauer             #+#    #+#             */
/*   Updated: 2024/07/28 18:16:47 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/all.h>

char	*t_char_list_to_str(t_mini *mini, t_char *list)
{
	char	*ret;
	t_char	*current;
	ssize_t	index;

	index = 0;
	current = list;
	if (!list)
		return (NULL);
	while (current)
	{
		++index;
		current = current->next;
	}
	ret = mini->malloc(mini, sizeof(char) * (index + 1));
	current = list;
	index = 0;
	while (current)
	{
		ret[index++] = current->c;
		current = current->next;
	}
	return (ret[index] = '\0', ret);
}

char	*t_word_to_str(t_mini *mini, t_word *word)
{
	char	*ret;
	t_char	*current_char;
	ssize_t	index;

	index = 0;
	current_char = word->c;
	while (current_char)
	{
		++index;
		current_char = current_char->next;
	}
	ret = mini->malloc(mini, sizeof(char) * (index + 1));
	index = 0;
	current_char = word->c;
	while (current_char)
	{
		ret[index++] = current_char->c;
		current_char = current_char->next;
	}
	return (ret[index] = '\0', ret);
}

ssize_t	t_word_list_len(t_word *words)
{
	ssize_t	ret;
	t_char	*current_char;

	ret = 0;
	while (words)
	{
		current_char = words->c;
		while (current_char)
		{
			++ret;
			current_char = current_char->next;
		}
		words = words->next;
	}
	return (ret);
}

char	*t_word_list_to_str(t_mini *mini, t_word *words)
{
	char	*ret;
	t_word	*current_word;
	t_char	*current_char;
	ssize_t	index;

	current_word = words;
	index = t_word_list_len(words);
	ret = mini->malloc(mini, sizeof(char) * (index + 1));
	index = 0;
	current_word = words;
	while (current_word)
	{
		current_char = current_word->c;
		while (current_char)
		{
			ret[index++] = current_char->c;
			current_char = current_char->next;
		}
		current_word = current_word->next;
	}
	return (ret[index] = '\0', ret);
}
