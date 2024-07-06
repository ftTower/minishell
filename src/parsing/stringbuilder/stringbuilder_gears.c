/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringbuilder_gears.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:20:46 by tauer             #+#    #+#             */
/*   Updated: 2024/07/06 02:26:04 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/all.h>

bool	t_char_list_maker(t_mini *mini, t_char **list, char **pipe_words)
{
	ssize_t	index;
	ssize_t	char_index;

	index = -1;
	while (pipe_words[++index])
	{
		char_index = -1;
		while (pipe_words[index][++char_index])
		{
			if ((pipe_words[index][char_index] == '<'
					|| pipe_words[index][char_index] == '>') && (char_index > 0
					&& (pipe_words[index][char_index - 1] != '<'
						&& pipe_words[index][char_index - 1] != '>')))
				char_t_char_add_back(mini, list, ' ');
			char_t_char_add_back(mini, list, pipe_words[index][char_index]);
		}
		char_t_char_add_back(mini, list, ' ');
	}
	return (false);
}

char	*string_constructor(t_mini *mini, t_char *list)
{
	char *ret;
	t_char *current;
	ssize_t index;

	index = -1;
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
	index = -1;
	while (current)
	{
		ret[++index] = current->c;
		current = current->next;
	}
	return (ret[index] = '\0', ret);
}