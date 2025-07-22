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

char	*skipc(char **s, char c)
{
	if (!s || !*s || !**s)
		return (NULL);
	while (**s && **s == c && **s != ' ')
		(*s)++;
	if (**s == ' ')
		(*s)++;
	return (*s);
}

char	*changec(char *s, char *c, char *to)
{
	int	i;
	int	j;

	if (!s || !*s)
		return (NULL);
	i = -1;
	while (s[++i])
	{
		j = -1;
		while (c[++j])
		{
			if (c[j] == s[i])
				s[i] = to[j % ft_strlen(to)];
		}
	}
	return (s);
}

int	get_c(char *str, char c)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != c)
		len++;
	return (len);
}

char	*add_c_end(t_solib *solib, char **str, char c)
{
	char	*new_str;
	int		len;

	len = ft_strlen(*str);
	new_str = somalloc(solib, sizeof(char) * (len + 2));
	ft_strlcpy(new_str, *str, len + 1);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	if (*str)
		free(*str);
	*str = new_str;
	return (new_str);
}

char	*display_prompt(t_mini *mini)
{
	(void)mini;
	char	*pwd;
	char	*prompt;

	pwd = getcwd(NULL, 0);
	//prompt = "> ";
	prompt = malloc(sizeof(char) * 1024); // Allocate memory for the prompt
	if (!prompt)
		return (NULL);
	snprintf(prompt, 1024, "\033[1;31m%s\033[0m \033[1;36m%s@%s\033[0m:\033[1;35m%s\033[0m > ",
		getenv("SHLVL") ? getenv("SHLVL") : "1",
		getenv("USER") ? getenv("USER") : "user",
		getenv("HOSTNAME") ? getenv("HOSTNAME") : "host",
		pwd);
	free(pwd);
	return (prompt);
}
