/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 23:48:45 by tauer             #+#    #+#             */
/*   Updated: 2024/07/03 02:22:09 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/all.h>

bool	cells_empty_pipe(t_mini *mini, char *raw_line)
{
	ssize_t	index;
	bool	empty;
	char	comp;

	comp = ' ';
	empty = true;
	index = -1;
	while (raw_line[++index])
	{
		if (raw_line[index] != ' ')
			comp = raw_line[index];
		if (raw_line[index] != ' ' && raw_line[index] != '|')
			empty = false;
		else if (raw_line[index] == '|' && empty)
			return (mini->print("found empty pipe\n"), true);
		else if (raw_line[index] == '|')
			empty = true;
	}
	if (comp == '|')
		return (mini->print("Invalid Token received\n"), true);
	return (false);
}
