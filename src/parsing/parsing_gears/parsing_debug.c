/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_debug.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/07/09 02:40:22 by tauer             #+#    #+#             */
/*   Updated: 2024/07/09 02:40:48 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/all.h>

void	print_t_char_list(t_mini *mini, t_char *list)
{
	t_char	*current;

	current = list;
	while (current)
	{
		print_t_char(mini, current, BLUE);
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
