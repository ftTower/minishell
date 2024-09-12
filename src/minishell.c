/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: almounib <almounib@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/04/11 21:31:29 by marvin            #+#    #+#             */
/*   Updated: 2024/05/20 17:40:22 by almounib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/all.h>
#include <sotypes/soprintf.h>


void mini_line_handler(t_mini *mini, char *line)
{
	if (*line)
		add_history(line);
	if (line && *line)
		mini_parsing(mini, line);
}

int minishell(t_solib *solib)
{
	t_mini *mini;

	mini = minit(solib);
	pre_parsing(mini);
	rl_initialize();
	while (mini->loop)
		mini_line_handler(mini, readline("prompt >"));
	return (mini->close(mini, EXIT_SUCCESS));
}