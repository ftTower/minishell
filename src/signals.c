/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 21:00:56 by marvin            #+#    #+#             */
/*   Updated: 2024/10/14 21:00:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/all.h>

static volatile sig_atomic_t	g_signal = 0;

sig_atomic_t	get_g_signal(void)
{
	return (g_signal);
}

void	set_g_signal(sig_atomic_t value)
{
	g_signal = value;
}
