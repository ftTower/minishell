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

// !!!!! TW PRINTF !!!!!!!

void display_path(t_mini *mini, char **promt)
{
	char **path;
	char *path_content;
	ssize_t index;
	ssize_t color_index;
	const char	*colors[] = {
		"\033[48;5;58m",
		"\033[48;5;59m",
		"\033[48;5;60m",
		"\033[48;5;61m",
		"\033[48;5;62m",
		"\033[48;5;63m",
		"\033[48;5;64m",
		"\033[48;5;65m",
	};
	char	*caracs;

	path_content = get_envpl_var(mini, "PWD");
	if (!path_content)
		return (caracs = ft_strdup(NULL, "\033[48;5;196mNO PATH\033[0m"), ft_strmcat(mini->solib, promt, caracs), free(caracs), (void)NULL);
	path = mini->libft->split(mini->solib,path_content ,'/');
	if (!path)
		return (caracs = ft_strdup(NULL, "\033[48;5;196mNO PATH\033[0m"), ft_strmcat(mini->solib, promt, caracs), free(caracs), (void)NULL);
	index = -1;
	color_index = -1;
	while(path[++index])
	{
		if (color_index == 8)
			color_index = 0;
		color_index++;
		if (index == 0)
		{
			printf("%s 📌 %s\033[0m", colors[color_index] ,path[index]);
		}
		else
		{
			printf("%s/%s\033[0m", colors[color_index] ,path[index]);
		}
	}
}

void display_user(t_mini *mini, char **promt)
{
	char	*info;
	char	*caracs;

	info = get_envpl_var(mini, "USER");
	caracs = ft_strdup(NULL, "\033[48;5;16m🧿 ");
	ft_strmcat(mini->solib, promt, caracs);
	ft_strmcat(mini->solib, promt, info);
	free(caracs);
	caracs = ft_strdup(NULL, " \033[0m");
	ft_strmcat(mini->solib, promt, caracs);
	free(caracs);
}

void display_info(t_mini *mini)
{	
	char *info;

	info = get_envpl_var(mini, "SHELL");
	printf("/\033[48;5;202m[%s]\033[0m-", info);
	info = get_envpl_var(mini, "SHLVL");
	printf("\033[48;5;202m[%s]\033[0m", info );
}
char	*display_prompt(t_mini *mini)
{
	//char *new_prompt = "      ˚ · .˚ ༘🦋⋆｡˚ )";
	//t_history_printer(mini);
	//new_prompt = ft_strdup(mini->solib, " \033[38;5;202m╭─\033[0m");
	//display_user(mini, &new_prompt);
	//display_path(mini, new_prompt)
	//display_info(mini, new_prompt);
	return (soprintf_get(mini->solib, "%s %C-if#57219e#292929( %s %C-b#696969() %C-b#0000ff(%s) )%C#292929() ",get_envpl_var(mini, "SHLVL"), getcwd(NULL, 0), get_envpl_var(mini, "USER")));
}
