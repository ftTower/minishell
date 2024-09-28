/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniformat_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 17:50:26 by tauer             #+#    #+#             */
/*   Updated: 2024/09/23 23:35:38 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/all.h>

char	*get_str(t_mini *mini, char c)
{
	char	*ret;

	ret = mini->malloc(mini, sizeof(char) * 2);
	ret[0] = c;
	ret[1] = '\0';
	return (ret);
}

bool	is_alpha(char compare)
{
	if ((compare >= 'a' && compare <= 'z') || (compare >= 'A' && compare <= 'Z'))
		return (true);
	return (false);
}

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
			if (current && current->c == '\\')
			{
				current = current->next;
				t_char_del_pos(mini, list, current->pos - 1);
			}
		}
		if (current)
			current = current->next;
	}
	print_t_char_list(mini, *list);
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
	mini->print("~%s~\n", ret);
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
			{
				t_char_add_pos(mini, list, current->pos, content[index]);	
			}
		current = current->next;
	}
}

bool	t_char_list_cat_var(t_mini *mini, t_char **list)
{
	t_char *current;
	char *buf_content;
	size_t buf_index;

	current = *list;
	print_t_char_list(mini, *list);
	while (current)
	{
		// if (current->c == '$' && current->next && !is_alpha(current->next->c))
		// 	;
		if (current->c == '$' && current->type_quotes != TYPEQUOTES_TO_KEEP)
		{
			buf_index = current->pos;
			buf_content = get_name_var(mini, list, buf_index);
			insert_var_content(mini, list, buf_index, buf_content);
			current = *list;
		}
		current = current->next;
	}
	return (false);
}