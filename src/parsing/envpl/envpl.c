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

bool	ft_strcmp(char *s1, char *s2)
{
	ssize_t index;

	index = -1;
	while (s1[++index] && s2[index])
		if (s1[index] != s2[index])
			return (false);
	if (s1[index] || s2[index])
		return (false);
	return (true);
}

char	*get_content_var(t_mini *mini, char *name_var)
{
	t_envpl *current;
	char	**name_tab;

	current = mini->envpl;
	while (current)
	{
		name_tab = mini->libft->split(mini->solib, current->var, '=');
		if (ft_strcmp(name_tab[0], name_var) && mini->libft->strlen(name_tab[0]) == mini->libft->strlen(name_var))
			return (current->var + mini->libft->strlen(name_tab[0]) + 1);
		current = current->next;
	}
	return (NULL);
}

bool	wrong_chars_str(char *str, char *wrong_chars)
{
	ssize_t index;
	ssize_t index_chars;

	index = -1;
	while (str[++index])
	{
		index_chars = -1;
		while (wrong_chars[++index_chars])
			if (str[index] == wrong_chars[index_chars])
				return (true);
	}
	return (false);
}

char	*extract_content_var(t_mini *mini, char *name_tofind_var)
{
	char *ret;

	ssize_t index;

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
	t_envpl *current;

	current = mini->envpl;
	if (!name_var)
		return (NULL);
	else if (wrong_chars_str(name_var, "| \\\"\'"))
		return (extract_content_var(mini, name_var));
	return (get_content_var(mini, name_var));
}

bool	add_var_envpl(t_mini *mini, t_envpl **envpl, char *var)
{
	t_envpl *new;

	new = mini->malloc(mini, sizeof(t_envpl));
	new->var = var;
	new->next = *envpl;
	*envpl = new;
	return (false);
}

bool	copy_envp_to_list(t_mini *mini)
{
	ssize_t index;

	index = -1;
	mini->envpl = NULL;
	if (!mini->env->envp)
		return (true);
	while (mini->env->envp[++index])
		add_var_envpl(mini, &mini->envpl, mini->env->envp[index]);
	return (false);
}

void	variable_content_setter(t_mini *mini, t_char **dst, char *content)
{
	ssize_t index;

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
	t_word *variable_name;
	t_char *current;

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
