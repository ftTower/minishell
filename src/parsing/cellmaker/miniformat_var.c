/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniformat_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/08/08 17:50:26 by tauer             #+#    #+#             */
/*   Updated: 2024/09/23 23:35:38 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/all.h>

void	delete_name_var(t_mini *mini, t_char **list, size_t pos)
{
	t_char			*current;
	t_type_quotes	buf;

	current = *list;
	while (current)
	{
		if (current->pos == pos)
		{
			current = current->next;
			t_char_del_pos(mini, list, current->pos - 1);
			while (current && is_alpha(current->c))
			{
				buf = current->type_quotes;
				current = current->next;
				t_char_del_pos(mini, list, current->pos - 1);
				if (current && current->type_quotes != buf)
					break ;
			}
		}
		if (current)
			current = current->next;
	}
}

char	*get_name_var(t_mini *mini, t_char **list, size_t pos)
{
	t_char	*current;
	char	*ret;

	ret = mini->libft->strdup(mini->solib, "");
	current = *list;
	while (current)
	{
		if (current->pos == pos + 1)
		{
			while (current && is_alpha(current->c))
			{
				if ((current->c == '$' && current->pos != pos))
					break ;
				mini->libft->strmcat(mini->solib, &ret, get_str(mini,
						current->c));
				if (current->next
					&& current->next->type_quotes != current->type_quotes)
					break ;
				current = current->next;
			}
		}
		if (current)
			current = current->next;
	}
	return (delete_name_var(mini, list, pos), get_envpl_var(mini, ret));
}

void	insert_var_content(t_mini *mini, t_char **list, size_t pos,
		char *content)
{
	t_char	*current;
	ssize_t	index;

	if (!content)
		return ;
	index = -1;
	current = *list;
	while (current)
	{
		if (current->pos == pos)
			while (content[++index])
				t_char_add_pos(mini, list, current->pos, content[index]);
		current = current->next;
	}
}

bool	t_char_replace_signal(t_mini *mini, \
t_char **list, t_char *current, char *str_signal)
{
	size_t	pos;

	if (current->next && current->next->c == '?')
	{
		current = current->next;
		pos = current->pos;
		t_char_del_pos(mini, list, pos);
		t_char_del_pos(mini, list, pos - 1);
		str_signal = mini->solib->libft->itoa(mini->solib, get_g_signal());
		insert_var_content(mini, list, pos - 1, str_signal);
		free(str_signal);
		return (true);
	}
	return (false);
}

void	t_char_list_cat_var(t_mini *mini, t_char **list)
{
	t_char	*current;
	char	*buf_content;
	size_t	buf_index;
	char	*str_signal;

	str_signal = NULL;
	current = *list;
	while (current)
	{
		if (current->c == '$' && ((current->next && !is_alpha(current->next->c)
					&& current->next->c != '?') || (!current->next)))
			current->type_quotes = TYPEQUOTES_TO_KEEP;
		else if (current->c == '$'
			&& current->type_quotes != TYPEQUOTES_TO_KEEP)
		{
			buf_index = current->pos;
			if (!t_char_replace_signal(mini, list, current, str_signal))
			{
				buf_content = get_name_var(mini, list, buf_index);
				insert_var_content(mini, list, buf_index, buf_content);
			}
			current = *list;
		}
		current = current->next;
	}
}
