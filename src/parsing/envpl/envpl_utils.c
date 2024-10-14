/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envpl_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 20:56:23 by tauer             #+#    #+#             */
/*   Updated: 2024/10/11 21:38:26 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/all.h>

void	del_var_envpl(t_mini *mini, char *var_name_to_del)
{
	t_envpl	*current;
	t_envpl	*tmp;

	if (!var_name_to_del)
		return ;
	current = mini->envpl;
	if (mini->libft->strncmp(current->next->var, var_name_to_del,
			var_name_size(current->next->var) - 1)
		&& var_name_size(current->next->var)
		- 1 == mini->libft->strlen(var_name_to_del))
		return (mini->envpl = mini->envpl->next, (void)0);
	while (current->next)
	{
		if (!mini->libft->strncmp(current->next->var, var_name_to_del,
				var_name_size(current->next->var) - 1)
			&& var_name_size(current->next->var)
			- 1 == mini->libft->strlen(var_name_to_del))
			return (tmp = current->next, current->next = tmp->next,
				mini->free(mini, tmp), (void)0);
		current = current->next;
	}
}

bool	add_var_envpl(t_mini *mini, char *var)
{
	t_envpl	*new;
	t_envpl	*current;

	current = mini->envpl;
	if (!current)
	{
		new = mini->malloc(mini, sizeof(t_envpl));
		new->var = var;
		new->next = NULL;
		mini->envpl = new;
		return (false);
	}
	while (current && current->next)
		current = current->next;
	new = mini->malloc(mini, sizeof(t_envpl));
	new->var = var;
	new->next = NULL;
	current->next = new;
	return (false);
}

bool	copy_envp_to_list(t_mini *mini)
{
	ssize_t	index;

	index = -1;
	mini->envpl = NULL;
	if (!mini->env->envp || !*mini->env->envp)
		return (add_var_envpl(mini, "SHLVL=0"), add_var_envpl(mini, "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"), \
				add_var_envpl(mini, "USER=DEFAULT") ,false);
	while (mini->env->envp[++index])
		add_var_envpl(mini, mini->env->envp[index]);
	return (false);
}
