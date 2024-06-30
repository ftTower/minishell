/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:08:01 by marvin            #+#    #+#             */
/*   Updated: 2024/06/05 18:08:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/all.h>

void add_t_char(t_mini *mini, t_char **line, char c, size_t pos)
{
	t_char *new;
	t_char *current;

	new = mini->malloc(mini, sizeof(t_char));
	new->c = c;
	new->pos = pos;
	new->next = NULL;
	new->quoted = false;
	new->useless = false;
	if (c != ' ')
		new->type = UNDEFINED;
	else
	{
		new->type = SPACE_CHAR;
		new->useless = true;
	}
	if (!*line)
		return (*line = new, (void)0);
	current = *line;
	while (current->next)
		current = current->next;
	return (current->next = new, (void)0);
}

void del_t_char(t_char **line, size_t pos_to_del)
{
	t_char *current;
	size_t correction_index;

	current = *line;
	while (current)
	{
		if (current->pos == pos_to_del - 1 && current->next && current->next->next)
		{
			current->next = current->next->next;
			break;
		}
		current = current->next;
	}
	current = *line;
	correction_index = 0;
	while (current)
	{
		current->pos = correction_index++;
		current = current->next;
	}
}

void type_t_char(t_char **line, size_t pos_to_type, t_char_type type)
{
	t_char *current;

	current = *line;
	while (current)
	{
		if (current->pos == pos_to_type)
			current->type = type;
		current = current->next;
	}
}

t_char *make_t_char_list(t_mini *mini, char *cell)
{
	t_char *line;
	size_t index;

	line = NULL;
	index = 0;
	while (cell[index])
	{
		add_t_char(mini, &line, cell[index], index);
		index++;
	}
	return (line);
}

void print_t_char(t_mini *mini, bool condition, char *str)
{
	if (condition)
		mini->print("%Cff0000(%s)", str);
	else
		mini->print("%C00ff6c(%s)", str);
}
