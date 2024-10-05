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
#include <solibft/sostring.h>

char    *skipc(char **s, char c)
{
    if (!s || !*s || !**s)
        return (NULL);
    while (**s && **s == c && **s != ' ')
        (*s)++;
    if (**s == ' ')
        (*s)++;
    return (*s);
}

int check_echo_option(char *s, char c)
{
    while (*s && *s != ' ')
    {
        if (*s != c)
            return (0);
        s++;
    }
    return (1);
}

char	*display_prompt(t_mini *mini)
{
	return (soprintf_get(mini->solib,
        "%s %C-if#57219e#292929( %s %C-b#696969() %C-b#0000ff((%d) - %s) )%C#292929() ",
        get_envpl_var(mini, "SHLVL"),
        getcwd(NULL, 0),
        g_signal,
        get_envpl_var(mini, "USER")));
}
