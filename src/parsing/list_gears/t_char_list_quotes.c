/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_char_list_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 21:08:31 by tauer             #+#    #+#             */
/*   Updated: 2024/10/11 21:38:26 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/all.h>

void	t_char_identify_bothquote(t_char *list)
{
	t_char			*current;
	t_type_quotes	quotes;

	current = list;
	quotes = TYPEQUOTES_UNSET;
	while (current)
	{
		if (current->c == (char)39)
			quotes = TYPEQUOTES_DOUBLE_QUOTED;
		else if (current->c == '"')
			quotes = TYPEQUOTES_TO_KEEP;
		if ((current->c == (char)39 || current->c == '"') && current->next
			&& current->next->type_quotes == TYPEQUOTES_BOTH_QUOTED)
		{
			current = current->next;
			while (current->next
				&& current->next->type_quotes == TYPEQUOTES_BOTH_QUOTED)
			{
				current->type_quotes = quotes;
				current = current->next;
				current->type_quotes = quotes;
			}
		}
		if (current)
			current = current->next;
	}
}

void	typequote_patern(t_char *current, bool double_quotes,
		bool single_quotes)
{
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
}

void	quotes_bool_switcher(t_char *current, bool *single_quotes,
		bool *double_quotes)
{
	if (current->c == '"')
	{
		if (!(*double_quotes) && !(*single_quotes))
			*double_quotes = true;
		else
			*double_quotes = false;
	}
	else if (current->c == (char)39)
	{
		if (!(*single_quotes) && !(*double_quotes))
			*single_quotes = true;
		else
			*single_quotes = false;
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
		quotes_bool_switcher(current, &single_quotes, &double_quotes);
		typequote_patern(current, double_quotes, single_quotes);
		current = current->next;
	}
	t_char_identify_bothquote(list);
}

void	t_char_print_typequote(t_mini *mini, t_char *list)
{
	t_char		*current;
	const char	*colors[] = {
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
