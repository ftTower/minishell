/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_print.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 21:14:57 by tauer             #+#    #+#             */
/*   Updated: 2024/10/11 21:38:25 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/all.h>

void	t_char_print_typequote(t_mini *mini, t_char *list)
{
	t_char		*current;
	const char	*colors[] = {
		"\033[38;5;220m",
		"\033[38;5;27m",
		"\033[48;5;50m",
		"\033[48;5;190m",
		"\033[48;5;75m",
		"\033[48;5;32m",
	};

	current = list;
	while (current)
	{
		mini->print("%s%c\033[0m", colors[current->type_quotes], current->c);
		current = current->next;
	}
}
