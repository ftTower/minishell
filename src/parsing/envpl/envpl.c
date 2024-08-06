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


char	*get_progressiv_name_var(t_mini *mini, char *name_var,
		size_t size_to_try)
{
	char *ret;
	if (!name_var || mini->libft->strlen(name_var) < size_to_try)
		return (NULL);
	ret = mini->malloc(mini, sizeof(char) * (size_to_try + 1));
	mini->libft->strlcpy(ret, name_var, size_to_try + 1);
	mini->print("%s %d\n", ret, size_to_try);
	return (ret);
}

char	*get_hidden_envpl_var(t_mini *mini, char *name_var)
{
	char *ret;
	char *buffer;
	size_t index;

	index = 1;
	mini->print("searching for hidden var [%s]\n", name_var);
	if (!name_var)
		return (NULL);
	while (index < mini->libft->strlen(name_var))
	{
		buffer = get_progressiv_name_var(mini, name_var, index);
		ret = get_envpl_var(mini, buffer);
		mini->print("%s\n", ret);
		if (ret)
			return (mini->print("found hidden var [%s] -> %s [%s]\n", name_var,
					buffer, ret), ret);
		mini->free(mini, buffer);
		index++;
	}
	return (NULL);
}

size_t	get_var_name_size(char *str)
{
	size_t index;

	index = 0;
	while (str[index])
	{
		if (str[index] == '=')
			return (index - 1);
		index++;
	}
	return (0);
}

char	*get_envpl_var(t_mini *mini, char *name_var)
{
	t_envpl *current;

	current = mini->envpl;
	if (!name_var)
		return (NULL);
	while (current)
	{
		// mini->print("%s [%d] %s[%d]\n", current->var, get_var_name_size(current->var), name_var, mini->libft->strlen(name_var));
		if (!mini->libft->strncmp(current->var, name_var,
				mini->libft->strlen(name_var)) && mini->libft->strlen(name_var) == get_var_name_size(current->var))
			return (current->var + mini->libft->strlen(name_var));
		current = current->next;
	}
	return (NULL);
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
