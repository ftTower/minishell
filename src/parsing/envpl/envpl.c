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
#include <solibft/sostring.h>

char	*get_content_var(t_mini *mini, char *name_var)
{
	t_envpl	*current;
	char	**name_tab;

	current = mini->envpl;
	while (current)
	{
		name_tab = mini->libft->split(mini->solib, current->var, '=');
		if (!ft_strcmp(name_tab[0], name_var)
			&& mini->libft->strlen(name_tab[0]) \
			== mini->libft->strlen(name_var))
			return (current->var + mini->libft->strlen(name_tab[0]) + 1);
		current = current->next;
	}
	return (NULL);
}

bool	wrong_chars_str(char *str, char *wrong_chars)
{
	ssize_t	index;
	ssize_t	index_chars;

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

bool	replace_envpl_var(t_mini *mini, char *var_name, char *to_replace)
{
	t_envpl	*current;

	current = mini->envpl;
	while (current)
	{
		if (!ft_strncmp(var_name, current->var, ft_strlen(var_name)))
			return (current->var = mini->libft->strjoin(mini->solib, var_name,
					to_replace), true);
		current = current->next;
	}
	return (false);
}

void	set_envpl_var(t_mini *mini, char *varname, char *to_replace)
{
	if (!get_envpl_var(mini, varname))
		add_var_envpl(mini, varname);
	replace_envpl_var(mini, varname, to_replace);
}

size_t	var_name_size(char *var)
{
	size_t	index;

	index = 0;
	while (var[index])
		if (var[index++] == '=')
			return (index);
	return (0);
}
