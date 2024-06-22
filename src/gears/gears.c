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
	return (state);
}


int mini_close(t_mini *mini, int state)
{
	if (mini)
		mini->free(mini, mini);
	if (state)
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
	mini->solib = solib;
	mini->libft =  solib->libft;
	mini->print =  solib->print;
	mini->env =  solib->env;
	mini->malloc =  mini_malloc;
	mini->free =  mini_free;
	mini->close = mini_close_update;
	return (mini);
}