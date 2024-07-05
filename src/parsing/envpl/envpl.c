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


char	*get_envpl_var(t_mini *mini, char *name_var)
{
	t_envpl *current;

	current = mini->envpl;
	while (current)
	{
		if (!mini->libft->strncmp(current->var, name_var,
				mini->libft->strlen(name_var)))
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
