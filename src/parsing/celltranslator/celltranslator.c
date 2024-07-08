/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:08:01 by marvin            #+#    #+#             */
/*   Updated: 2024/06/05 18:08:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/all.h>

bool	t_word_list_has_type(t_word *words, t_type type)
{
	t_word *current;

	current = words;
	while (current)
	{
		if (current->type == type)
			return (true);
		current = current->next;
	}
	return (false);
}

// bool 	t_cell_pipe_translator(t_mini *mini, t_cell *cell, ssize_t index)
// {
// 	if (index == 0)
// 	{

// 	}
// 	else if (index > 0)
// 	{

// 	}
// }	

bool	celltranslator_translator(t_mini *mini, t_cell *cell)
{
	// ssize_t index;

	// index = -1;
	// while(++index < cell->nb_pipes)
	// 	t_cell_pipe_translator(mini, cell, index);
	
	mini->print("%d\n", cell->pos);
	return (false);
}
