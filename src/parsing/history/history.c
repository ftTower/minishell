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

// typedef struct s_history
// {
// 	char *line;
// 	ssize_t pos;
// 	struct s_history *next;
// }	t_history;

void	t_history_final_lines_print(t_mini *mini, t_cell *cell)
{
	ssize_t index;
	ssize_t index2;
	t_pipex *current;

	current = cell->final_line;
	index2 = 0;
	while(current)
	{
		mini->print(" [%d:", index2);
		mini->print("%C07f406(%s) ", current->in_fd);
		index = -1;
		while(current->args[++index])
			mini->print("%s ",current->args[index]);
		mini->print("%Cf43006(%s)]", current->out_fd);
		current = current->next;
		index2++;
	}
}

void	t_history_print(t_mini *mini, t_history *current)
{
	mini->print("\033[48;5;166m %d \033[0m", current->pos);
	if (current->success)
		t_history_final_lines_print(mini, current->cell);
	else
	{
		mini->print("\033[48;5;160m");
		if (mini->history_pos == current->pos)
			mini->print("\033[5m %s\033[0m\033[0m", current->line);
		else
			mini->print(" %s\033[0m", current->line);
	}
	mini->print("\n");
}

void	t_history_printer(t_mini *mini)
{
	t_history *current;
	ssize_t index;

	index = 0;
	current = mini->history;
	mini->print("\n");
	if (!mini->history)
		return ;
	while(current)
	{
		index++;
		current = current->next;
	}
	current = mini->history;
	while(current)
	{
		if (current->pos > index - 4)
			t_history_print(mini, current);
		current = current->next;
	}
	mini->print("\n");
}

char  *t_history_get_line(t_mini *mini, ssize_t pos)
{
	t_history *current;

	current = mini->history;
	if (pos < 0)
	{
		while(current->next)
			current = current->next;
		return (current->line);
	}
	while(current)
	{
		if (current->pos == pos)
			return (current->line);
		current = current->next;
	}
	return (mini->history->line);
}

void t_history_add_line(t_mini *mini, char *line, bool success, t_cell *cell)
{
    t_history *new;
    t_history *current;
    ssize_t pos;

    new = mini->malloc(mini, sizeof(t_history));
    new->line = line;
    new->next = NULL;
	new->cell = cell;
	new->success = success;
    pos = 0;
    if (!mini->history)
    {
        new->pos = pos;
        mini->history = new;
        return;
    }
    current = mini->history;
    while (current->next)
    {
        pos++;
        current = current->next;
    }
    new->pos = pos + 1;
    current->next = new;
}
