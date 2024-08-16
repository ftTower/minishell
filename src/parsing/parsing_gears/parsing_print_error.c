/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_print_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 01:29:59 by tauer             #+#    #+#             */
/*   Updated: 2024/08/17 00:48:15 by tauer            ###   ########.fr       */
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

void	print_error_input(t_mini *mini, char *input, char *char_error)
{
	ssize_t index;

	index = -1;
	mini->print("\n\t");
	while(input[++index])
	{
		if (is_chars(input[index], char_error))
			mini->print("\033[48;5;196m%c\033[0m", input[index]);
		else
			mini->print("\033[38;5;231m%c\033[0m", input[index]);
		usleep(100000);
	}
	mini->print("\n");
}

void	print_char_error(t_mini *mini, char *input, char *char_error,
		char *error_msg)
{
	size_t	len;

	len = mini->libft->strlen(get_envpl_var(mini, "USER"))
		+ mini->libft->strlen(get_envpl_var(mini, "PWD")) + 7;
	mini->print("\n\t\033[38;5;196mMinishell \033[5m%s\033[0m\033[0m\n ", error_msg);
	print_error_input(mini, input, char_error);
}

void	handle_error(t_mini *mini, char *input, t_error_code code)
{
	if (code == ERROR_UNSET)
		return ;
	else if (code == ERROR_EMPTY_SEMICOLON)
		print_char_error(mini, input, ";", "found an empty semicolon");
	else if (code == ERROR_EMPTY_PIPE)
		print_char_error(mini, input, "|", "found an empty pipe");
	else if (code == ERROR_EMPTY_REDIRECT || code == ERROR_INVALID_REDIRECT)
		print_char_error(mini, input, "<>", "found an invalid redirect");
	else if (code == ERROR_FAILED_OPEN_IN_FD)
		print_char_error(mini, input, "<", "failed to open input file");
	else if (code == ERROR_FAILED_OPEN_OUT_FD)
		print_char_error(mini, input, ">", "failed to open output file");
	else if (code == ERROR_TOO_MANY_REDIRECT)
		print_char_error(mini, input, "><", "found too many redirects");
}
