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

void	t_history_print(t_mini *mini)
{
	t_history *current;

	current = mini->history;
	mini->print("\n");
	if (!mini->history)
		return (mini->print("no history\n"), (void)0);
	while(current)
	{
		if (current->success)
			mini->print("✅ ");
		else
			mini->print("❌ ");
		mini->print("%d ", current->pos);
		if (mini->history_pos == current->pos)
			mini->print("\033[5m%s\033[0m", current->line);
		else
			mini->print("%s", current->line);
		mini->print("\n");
		current = current->next;
	}
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

void t_history_add_line(t_mini *mini, char *line, bool success)
{
    t_history *new;
    t_history *current;
    ssize_t pos;

    new = mini->malloc(mini, sizeof(t_history));
    new->line = line;
    new->next = NULL;
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
