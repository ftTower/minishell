/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_print_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 01:29:59 by tauer             #+#    #+#             */
/*   Updated: 2024/08/16 03:06:14 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/all.h>

bool	is_chars(char c, char *chars)
{
	ssize_t	index;

	index = -1;
	while (chars[++index])
		if (c == chars[index])
			return (true);
	return (false);
}

void	print_line(t_mini *mini)
{
	size_t	index;

	const char *colors[] = {
		"\033[48;5;202m",
		"\033[48;5;15m",
	};
	index = 0;
	while (index < mini->libft->strlen(get_envpl_var(mini, "USER")) + 4)
	{
		mini->print("%s \033[0m", colors[0]);
		usleep(100000);
		++index;
	}
	while (index < mini->libft->strlen(get_envpl_var(mini, "USER")) + 3
		+ mini->libft->strlen(get_envpl_var(mini, "PWD")) + 4)
	{
		mini->print("%s \033[0m", colors[1]);
		usleep(1000);
		++index;
	}
	mini->print("\n");
}

void	print_char_error(t_mini *mini, char *input, char *char_error,
		char *error_msg)
{
	size_t	len;

	len = mini->libft->strlen(get_envpl_var(mini, "USER"))
		+ mini->libft->strlen(get_envpl_var(mini, "PWD")) + 7;
	print_line(mini);
	
	print_line(mini);
	input = NULL;
	char_error = NULL;
	error_msg = NULL;
}

void	print_error(t_mini *mini, char *input, t_error_code code)
{
	if (code == ERROR_UNSET)
		return ;
	else if (code == ERROR_EMPTY_SEMICOLON)
		print_char_error(mini, input, ";", "Empty semicolon : ");
	else if (code == ERROR_EMPTY_PIPE)
		print_char_error(mini, input, "|", "Empty pipe : ");
	else if (code == ERROR_EMPTY_REDIRECT || code == ERROR_INVALID_REDIRECT)
		print_char_error(mini, input, "<>", "Empty or invalid redirect : ");
	else if (code == ERROR_FAILED_OPEN_IN_FD)
		print_char_error(mini, input, "<", "Failed to open input file : ");
	else if (code == ERROR_FAILED_OPEN_OUT_FD)
		print_char_error(mini, input, ">", "Failed to open output file : ");
}
