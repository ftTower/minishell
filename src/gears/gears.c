/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:08:01 by marvin            #+#    #+#             */
/*   Updated: 2024/06/05 18:08:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/all.h>

int mini_close_update(t_mini *mini, int state)
{
	if (mini)
		mini->loop = 0;
	
	if (state)
		mini_close(mini, state);
	mini_close(mini, state);
	return (state);
}


int mini_close(t_mini *mini, int state)
{
	if (state)
		exit(mini->solib->close(mini->solib, state));
	exit(mini->solib->close(mini->solib, state));
	return (state);
}

void	*mini_malloc(t_mini *mini, size_t size)
{
	return (mini->solib->malloc(mini->solib, size));
}

int	mini_free(t_mini *mini, void *ptr)
{
	return (mini->solib->free(mini->solib, ptr));
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
	while(mini->env->envp[++index])
	{
		// mini->print("before : %s\n", mini->env->envp[index]);	
		add_var_envpl(mini, &mini->envpl, mini->env->envp[index]);
	}
	return (false);
}

void	print_envpl(t_mini *mini)
{
	t_envpl *current;

	current = mini->envpl;
	while(current)
	{
		mini->print("%s\n", current->var);
		current = current->next;
	}
}

t_mini	*minit(t_solib *solib)
{
	t_mini	*mini;

	if (!solib)
		solib = sonew_types(0, NULL, NULL);
	if (!solib)
		exit(EXIT_FAILURE);
	if (!solib->libft)
		solib = sonew_libft(solib);
	if (!solib->libft)
		solib->close(solib, EXIT_FAILURE);
	mini = (t_mini *)solib->malloc(solib, sizeof(t_mini));
	if (!mini)
		solib->close(solib, EXIT_FAILURE);
	mini->loop = 1;
	mini->starting = 0;
	mini->solib = solib;
	mini->libft =  solib->libft;
	mini->print =  solib->print;
	mini->env =  solib->env;
	mini->malloc =  mini_malloc;
	mini->free =  mini_free;
	mini->close = mini_close_update;
	if (copy_envp_to_list(mini))
		solib->close(solib, EXIT_FAILURE);
	print_envpl(mini);
	return (mini);
}