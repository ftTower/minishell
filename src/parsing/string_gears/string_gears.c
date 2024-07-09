/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringbuilder_gears.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:20:46 by tauer             #+#    #+#             */
/*   Updated: 2024/07/09 01:54:26 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/all.h>

char	*t_char_list_to_str(t_mini *mini, t_char *list)
{
	char *ret;
	t_char *current;
	ssize_t index;

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