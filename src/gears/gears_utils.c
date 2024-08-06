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
#include <sotypes/soprintf.h>

void line_handler() // pas touche a ca ! okok... ;(
{
	return ;
}

// !!!!! TW PRINTF !!!!!!!

void display_path(t_mini *mini)
{
	char **path;
	char *path_content;
	ssize_t index;
	ssize_t color_index;
	const char	*colors[] = {
		"\033[48;5;25m",
		"\033[48;5;63m",
		"\033[48;5;122m",
		"\033[48;5;153m",
		"\033[48;5;159m",
		"\033[48;5;189m",
		"\033[48;5;195m",
		"\033[48;5;226m",
	};

	path_content = get_envpl_var(mini, "PWD=");
	if (!path_content)
		return (printf("\033[48;5;196mNO PATH\033[0m"), (void)NULL);
	path = mini->libft->split(mini->solib,path_content ,'/');
	if (!path)
		return (printf("\033[48;5;196mNO PATH\033[0m"), (void)NULL);
	index = -1;
	color_index = -1;
	while(path[++index])
	{
		if (color_index == 8)
			color_index = 0;
		color_index++;
		if (index == 0)
			printf("%s📌 %s\033[0m", colors[color_index] ,path[index]);
		else
			printf("%s/%s\033[0m", colors[color_index] ,path[index]);
	}
}

void display_info(t_mini *mini)
{
	char *info;

	info = get_envpl_var(mini, "USER=");
	printf("\033[48;5;202m🧿 %s\033[0m-", info);
	info = get_envpl_var(mini, "SHELL=");
	printf("\033[48;5;202m[%s\033[0m", info);
	info = get_envpl_var(mini, "SHLVL=");
	printf("\033[48;5;202m: %s]\033[0m-", info);
}

void display_prompt(t_mini *mini)
{
	printf(" \033[38;5;202m╭─\033[0m");
	display_info(mini);
	display_path(mini);
	printf("\n ╰─ ");
}

void mini_prompt(t_mini *mini)
{
	rl_replace_line("", -1); // Efface la ligne courante
	//soprintf("%C22d8db(%s)%s", ft_get_dictionary("promt"), ft_get_dictionary("promt"));
	// soprintf("[MINISHELL]\t> ");
	display_prompt(mini);
	// soprintf(" ╭─%Cff0000([)%Cf1c40f(%s)%Cff0000(])\n ╰─ ", get_envpl_var(mini, "PWD="));
	rl_on_new_line(); // Remet le prompt sur une nouvelle ligne
	rl_redisplay();	  // Redess
}