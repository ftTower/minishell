/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_char_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 01:43:38 by tauer             #+#    #+#             */
/*   Updated: 2024/08/17 00:38:24 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/all.h>

void	t_char_print_typequote(t_mini *mini, t_char *list)
{
	t_char	*current;

	const char *colors[] = {
		"\033[38;5;220m",
		"\033[38;5;27m",
		"\033[48;5;46m",
		"\033[48;5;196m",
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

void	t_char_identify_bothquote(t_char *list)
{
	t_char *current = list;

	while(current)
	{
		if (current->c == (char)39 && current->next && current->next->type_quotes == TYPEQUOTES_BOTH_QUOTED)
		{
			current = current->next;
			while(current->next && current->next->type_quotes == TYPEQUOTES_BOTH_QUOTED)
			{
				current->type_quotes = TYPEQUOTES_DOUBLE_QUOTED;
				current = current->next;
				current->type_quotes = TYPEQUOTES_DOUBLE_QUOTED;
			}
		}
		else if (current->c == '"' && current->next && current->next->type_quotes == TYPEQUOTES_BOTH_QUOTED)
		{
			current = current->next;
			while(current->next && current->next->type_quotes == TYPEQUOTES_BOTH_QUOTED)
			{
				current->type_quotes = TYPEQUOTES_TO_KEEP;
				current = current->next;
				current->type_quotes = TYPEQUOTES_TO_KEEP;
			}
		}
		if (current)
			current = current->next;
	}
}

void	t_char_identify_typequote(t_char *list)
{
	t_char	*current;
	bool	double_quotes;
	bool	single_quotes;

	double_quotes = false;
	single_quotes = false;
	current = list;
	while (current)
	{
		if (current->c == '"')
		{
			if (!double_quotes)
				double_quotes = true;
			else
				double_quotes = false;
		}
		else if (current->c == (char)39)
		{
			if (!single_quotes)
				single_quotes = true;
			else
				single_quotes = false;
		}
		if ((current->c == '"' && single_quotes) || (current->c == (char)39
			&& double_quotes))
			current->type_quotes = TYPEQUOTES_TO_KEEP;
		else if (current->c == '"')
			current->type_quotes = TYPEQUOTES_DOUBLE_QUOTED;
		else if (current->c == (char)39)
			current->type_quotes = TYPEQUOTES_SINGLE_QUOTED;
		else if (!double_quotes && !single_quotes)
			current->type_quotes = TYPEQUOTES_UNQUOTED;
		else if (double_quotes && single_quotes)
			current->type_quotes = TYPEQUOTES_BOTH_QUOTED;
		else if (!double_quotes && single_quotes)
			current->type_quotes = TYPEQUOTES_TO_KEEP;
		else if (double_quotes && !single_quotes)
			current->type_quotes = TYPEQUOTES_DOUBLE_QUOTED;
		current = current->next;
	}
	t_char_identify_bothquote(list);
}

bool	char_add_back(t_mini *mini, t_word *word, char c)
{
	t_char	*new;
	t_char	*current;

	new = mini->malloc(mini, sizeof(t_char));
	new->c = c;
	new->type_quotes = TYPEQUOTES_UNSET;
	new->next = NULL;
	if (!word || !word->c)
		return (word->c = new);
	current = word->c;
	while (current->next)
		current = current->next;
	return (current->next = new, false);
}

bool	char_t_char_add_back(t_mini *mini, t_char **list, char c)
{
	t_char	*new;
	t_char	*current;

	new = mini->malloc(mini, sizeof(t_char));
	new->c = c;
	new->type_quotes = TYPEQUOTES_UNSET;
	new->next = NULL;
	if (!(*list) || !(*list)->c)
		return ((*list) = new, false);
	current = (*list);
	while (current->next)
		current = current->next;
	return (current->next = new, false);
}

bool	strr_to_t_char_list(t_mini *mini, t_char **dst, char **src)
{
	ssize_t	index;
	ssize_t	char_index;

	index = -1;
	while (src[++index])
	{
		char_index = -1;
		while (src[index][++char_index])
		{
			if ((src[index][char_index] == '<' || src[index][char_index] == '>')
				&& (char_index > 0 && (src[index][char_index - 1] != '<'
						&& src[index][char_index - 1] != '>')))
				char_t_char_add_back(mini, dst, ' ');
			char_t_char_add_back(mini, dst, src[index][char_index]);
		}
		char_t_char_add_back(mini, dst, ' ');
	}
	return (false);
}

void	t_char_set_pos(t_char *list)
{
	ssize_t	index;

	index = 0;
	while (list)
	{
		list->pos = index++;
		list = list->next;
	}
}

bool	t_char_add_pos(t_mini *mini, t_char **dst, size_t pos, char c)
{
	t_char	*new;
	t_char	*current;
	t_char	*previous;

	new = mini->malloc(mini, sizeof(t_char));
	new->c = c;
	new->type_quotes = TYPEQUOTES_UNSET;
	new->next = NULL;
	t_char_set_pos((*dst));
	current = (*dst);
	previous = NULL;
	while (current)
	{
		if (current->pos == pos)
		{
			if (previous)
				previous->next = new;
			else
				(*dst) = new;
			new->next = current;
			t_char_set_pos((*dst));
			return (false);
		}
		previous = current;
		current = current->next;
	}
	return (true);
}

bool	t_char_del_pos(t_mini *mini, t_char **list, size_t pos_to_del)
{
	t_char	*current;
	t_char	*tmp;

	if (pos_to_del == 0)
		return (*list = (*list)->next, false);
	t_char_set_pos(*list);
	current = (*list);
	while (current)
	{
		if (current->next && current->next->pos == pos_to_del)
			return (tmp = current->next, current->next = tmp->next,
				mini->free(mini, tmp), t_char_set_pos(*list), false);
		current = current->next;
	}
	return (false);
}
