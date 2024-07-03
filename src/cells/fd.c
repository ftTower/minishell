/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 01:46:21 by tauer             #+#    #+#             */
/*   Updated: 2024/07/04 01:49:33 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/all.h>

bool	fd_getter(t_mini *mini, t_char *current, t_pipe *pipe)
{
	t_char *word_rest;

	word_rest = current->next;
	printf("fd getter\n");
	while (word_rest)
	{
		print_t_char(mini, word_rest, RED);
		word_rest = word_rest->next;
	}
	mini->print("%d\n", pipe->pos);
	return (false);
}

bool	fd_watcher(t_mini *mini, t_word *word, t_pipe *pipe)
{
	t_char *current;

	current = word->c;
	while (current)
	{
		if (((current->next && (current->next->c == '<'
						|| current->next->c == '>')) || (current->pos == 0
					&& (current->c == '<' || current->c == '>')))
			&& fd_getter(mini, current, pipe))
			return (true);
		current = current->next;
	}
	return (false);
}
