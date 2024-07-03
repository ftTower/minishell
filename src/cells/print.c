/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 01:09:03 by tauer             #+#    #+#             */
/*   Updated: 2024/07/03 02:40:49 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/all.h>

void	print_t_char(t_mini *mini, t_char *c, bool lignfeed)
{
	if (lignfeed)
		mini->print("%c\n", c->c);
	else
		mini->print("%c", c->c);
}

void	print_t_word(t_mini *mini, t_word *word)
{
	t_char	*current;

	current = word->c;
	while (current)
	{
		print_t_char(mini, current, false);
		current = current->next;
	}
	mini->print("\n");
}

void	print_t_pipe(t_mini *mini, t_pipe *pipe)
{
	t_word	*current;

	current = pipe->words;
	while (current)
	{
		print_t_word(mini, current);
		current = current->next;
	}
}

void	print_double_tab(t_mini *mini, char **tab)
{
	ssize_t	index;

	index = -1;
	if (!tab)
		return ;
	while (tab[++index])
		mini->print("%s\n", tab[index]);
}
