/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chars.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 02:20:29 by tauer             #+#    #+#             */
/*   Updated: 2024/07/04 01:20:46 by tauer            ###   ########.fr       */
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
