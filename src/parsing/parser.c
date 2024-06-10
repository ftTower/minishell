/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pswp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almounib <almounib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 18:16:39 by marvin            #+#    #+#             */
/*   Updated: 2024/05/16 15:15:49 by almounib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/all.h>
#include <sotypes/soprintf.h>

int	parser(t_solib *solib)
{
	solib->print("parser\n");
	return (0);
}