/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envpl_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 20:57:11 by tauer             #+#    #+#             */
/*   Updated: 2024/10/11 21:01:54 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/all.h>

void	variable_content_setter(t_mini *mini, t_char **dst, char *content)
{
	ssize_t	index;

	index = -1;
	if (!content)
		return ;
	t_char_set_pos((*dst));
	while (content[++index])
		;
	while (index > 0)
		t_char_add_pos(mini, dst, (*dst)->pos, content[index--]);
}

char	*variable_content_getter(t_mini *mini, t_char **dst)
{
	t_word	*variable_name;
	t_char	*current;

	variable_name = mini->malloc(mini, sizeof(t_word));
	variable_name->c = NULL;
	variable_name->next = NULL;
	current = (*dst);
	while (current && current->c != ' ')
	{
		if (current->c != '$')
			char_add_back(mini, variable_name, current->c);
		current = current->next;
	}
	return (get_envpl_var(mini, t_word_list_to_str(mini, variable_name)));
}

char	*extract_content_var(t_mini *mini, char *name_tofind_var)
{
	char	*ret;
	ssize_t	index;

	index = -1;
	while (name_tofind_var[++index])
		if (name_tofind_var[index] == '|' || name_tofind_var[index] == '\\'
			|| name_tofind_var[index] == '"'
			|| name_tofind_var[index] == (char)39)
			break ;
	ret = mini->libft->substr(mini->solib, name_tofind_var, 0, index);
	ret = get_envpl_var(mini, ret);
	if (!ret)
		return (name_tofind_var + index);
	mini->libft->strmcat(mini->solib, &ret, name_tofind_var + index);
	return (ret);
}

char	*get_envpl_var(t_mini *mini, char *name_var)
{
	if (!name_var)
		return (NULL);
	else if (wrong_chars_str(name_var, "| \\\"\'"))
		return (extract_content_var(mini, name_var));
	return (get_content_var(mini, name_var));
}
