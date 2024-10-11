/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 20:22:15 by marvin            #+#    #+#             */
/*   Updated: 2024/10/11 21:18:16 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/all.h>
#include <solibft/sostring.h>
#include <solibft/sostdlib.h>
#include <solibft/soctype.h>

int	set_exit_status(char *str)
{
	int	i;
	if (!str)
		return (g_signal = 0, 0);
	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]) && str[i] != ' ')
			return (g_signal = 2, 0);
	}
	g_signal = (int)ft_atoi(str);
	return (0);
}

int	hub_builtin(t_mini *mini, char *cmd, int pipefd[2])
{
	if (!ft_strncmp("exit", cmd, 4))
		return (cmd += 4, close_pipe(pipefd), set_exit_status(cmd), mini->close(mini, g_signal), 1);
	if (!ft_strncmp("echo -", cmd, 6) && check_echo_option(cmd + 6, 'n'))
		return (cmd += 6, changec(cmd, '|', ' '), putstrfd(skipc(&cmd, 'n'), pipefd[1]), close_pipe(pipefd), 1);
	if (!ft_strncmp("cd", cmd, 2))
		return (cmd += 3, is_raw_path(mini, changec(cmd, '|', ' ')), close_pipe(pipefd), 1);
	if (!ft_strncmp("pwd", cmd, 3))
		return (putstrfd(getcwd(NULL, 0), pipefd[1]),
			putstrfd("\n", pipefd[1]), close_pipe(pipefd), 1);
	if (!ft_strncmp("export", cmd, 6))
		return (cmd += 7, handle_export(mini, changec(cmd, '|', ' '), pipefd[1]), close_pipe(pipefd), 1);
	if (!ft_strncmp("unset", cmd, 5))
		return (cmd += 6, del_var_envpl(mini, changec(cmd, '|', ' ')), close_pipe(pipefd), 1);
	if (!ft_strncmp("env\0", cmd, 4))
		return (print_envpl(pipefd[1], mini), close_pipe(pipefd), 1);
	return (0);
}

void handle_export(t_mini *mini, char *cmd, int fd)
{
	char	**exs;
	char	*varname;
	char	*varlue;
	int		i;	

	if (!*cmd)
		return print_envpl(fd, mini);
	exs = ft_split(mini->solib, cmd, ' ');
	i = -1;
	while (exs[++i])
	{
		varlue = ft_substr(NULL, exs[i], get_c(exs[i], '=') + 1, ft_strlen(exs[i]));
		varname = ft_substr(NULL, exs[i], 0, get_c(exs[i], '='));
		set_envpl_var(mini, add_c_end(mini->solib, &varname, '='), varlue);
		free(varname);
		free(varlue);
	}
}