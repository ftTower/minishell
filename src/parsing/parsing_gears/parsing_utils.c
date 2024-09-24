/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:20:46 by tauer             #+#    #+#             */
/*   Updated: 2024/07/31 00:12:44 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/all.h>

bool	strtlen(char **tab, ssize_t *ret)
{
	*ret = 0;
	if (!tab || !*tab)
		return (true);
	while (tab[*ret])
		(*ret)++;
	return (false);
}

void	free_tab(char **tab)
{
	ssize_t	index;

	index = -1;
	while (tab[++index])
		free(tab[index]);
	free(tab);
}
