/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/06/05 18:08:01 by marvin            #+#    #+#             */
/*   Updated: 2024/06/05 18:08:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/all.h>


void	print_double_tab(t_mini *mini, char **tab)
{
	ssize_t index;

	index = -1;
	while (tab[++index])
		mini->print("%s\n", tab[index]);
}

bool	cells_empty_pipe(t_mini *mini, char *raw_line)
{
	ssize_t index;
	bool empty;
	char comp;

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
		return (mini->print("found empty pipe a the end\n"), true);
	return (false);
}

char	**cells_liner(t_mini *mini, char *raw_line)
{
	char **ret;

	ret = NULL;
	if (!raw_line || !*raw_line || cells_empty_pipe(mini, raw_line))
		return (mini->print("error in cells_liner\n"), NULL);
	return (ret);
}

void	cells_handler(t_mini *mini, char *raw_line)
{
	t_cell *cell;

	mini->print("\n> %s\n", raw_line);
	cell = mini->malloc(mini, sizeof(t_cell));

	cells_liner(mini, raw_line);


}
