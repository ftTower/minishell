/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 01:09:03 by tauer             #+#    #+#             */
/*   Updated: 2024/07/04 01:50:05 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/all.h>

void print_t_char(t_mini *mini, t_char *c, t_color color)
{
    if (color == ORANGE)
        mini->print("%Ce67e22(%c)", c->c);
    else if (color == PURPLE)
        mini->print("%Cc238eb(%c)", c->c);
    else if (color == YELLOW)
        mini->print("%Cf1c40f(%c)", c->c);
    else if (color == GREEN)
        mini->print("%C2ecc71(%c)", c->c);
    else if (color == RED)
        mini->print("%Cff0000(%c)", c->c);
	 else if (color == BLUE)
        mini->print("%C5dade2(%c)", c->c);
    else
        mini->print("%Cffffff(%c)", c->c);
}

void	print_t_word(t_mini *mini, t_word *word)
{
	t_char	*current;

	current = word->c;
	while (current)
	{
		if (word->type == CMD_TYPE)
			print_t_char(mini, current, GREEN);
		else if (word->type == PARA_TYPE)
			print_t_char(mini, current, YELLOW);
		else if (word->type == ARG_TYPE)
			print_t_char(mini, current, BLUE);
		else
			print_t_char(mini, current, RED);
		current = current->next;
	}
	mini->print("\t");
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
	mini->print("\n");
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
