/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/07/05 15:20:46 by tauer             #+#    #+#             */
/*   Updated: 2024/07/31 00:12:44 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/all.h>

void	char_bool_quotes_switcher(char c, bool *single, bool *double_)
{
	if (c == '"')
	{
		if (!*double_)
			*double_ = true;
		else
			*double_ = false;
	}
	else if (c == (char)39)
	{
		if (!*single)
			*single = true;
		else
			*single = false;
	}
}

char	*get_str(t_mini *mini, char c)
{
	char	*ret;

	ret = mini->malloc(mini, sizeof(char) * 2);
	ret[0] = c;
	ret[1] = '\0';
	return (ret);
}

bool	is_alpha(char compare)
{
	if ((compare >= 'a' && compare <= 'z') || (compare >= 'A' && compare <= 'Z')
		|| (compare >= '0' && compare <= '9'))
		return (true);
	return (false);
}

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
