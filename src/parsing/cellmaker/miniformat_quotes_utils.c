/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniformat_quotes_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 20:15:06 by tauer             #+#    #+#             */
/*   Updated: 2024/10/11 20:38:02 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/all.h>

bool	is_quoted(char *str, ssize_t index)
{
	ssize_t	start;

	start = index;
	while (start > 0 && str[start] != '"')
		--start;
	while (str[++index])
		if (str[start] == '"' && str[index] == '"')
			return (true);
	return (false);
}

char	*preserve_space_in_quote(t_mini *mini, char *str_to_dup)
{
	ssize_t	index;
	char	*dup;
	bool	double_quotes;

	double_quotes = false;
	index = -1;
	dup = mini->malloc(mini, sizeof(char) * (mini->libft->strlen(str_to_dup)
				+ 1));
	while (str_to_dup[++index])
	{
		if (str_to_dup[index] == '"')
		{
			if (!double_quotes)
				double_quotes = true;
			else
				double_quotes = false;
		}
		if (str_to_dup[index] == ' ' && double_quotes)
			dup[index] = '|';
		else
			dup[index] = str_to_dup[index];
	}
	return (dup[index] = '\0', dup);
}

bool	unclosed_quotes(t_mini *mini, t_char **list)
{
	t_char	*current;
	ssize_t	count_double;
	ssize_t	count_single;

	count_double = 0;
	count_single = 0;
	current = *list;
	while (current)
	{
		if (current->c == '"' && current->type_quotes != TYPEQUOTES_TO_KEEP)
			count_double++;
		else if (current->c == (char)39
			&& current->type_quotes != TYPEQUOTES_TO_KEEP)
			count_single++;
		current = current->next;
	}
	if (count_double % 2 != 0 || count_single % 2 != 0)
		return (handle_error(mini, t_char_list_to_str(mini, *list),
				ERROR_TYPE_UNCLOSED_QUOTES), true);
	return (false);
}

void	t_char_del_quotes(t_mini *mini, t_char **list)
{
	t_char	*current;

	current = *list;
	while (current)
	{
		if ((current->c == (char)39 || current->c == '"')
			&& current->type_quotes != TYPEQUOTES_TO_KEEP)
		{
			current = current->next;
			t_char_del_pos(mini, list, current->pos - 1);
		}
		else
			current = current->next;
	}
}

void	t_char_del_pos_safe(t_mini *mini, t_char **list, t_char **current)
{
	t_char	*next;

	next = (*current)->next;
	t_char_del_pos(mini, list, (*current)->pos);
	*current = next;
}
