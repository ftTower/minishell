/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 20:22:15 by marvin            #+#    #+#             */
/*   Updated: 2024/10/14 22:53:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/all.h>
#include <solibft/sostring.h>
#include <solibft/sostdlib.h>
#include <solibft/soctype.h>

int	check_echo_option(char *s, char c)
{
	while (*s && *s != ' ')
	{
		if (*s != c)
			return (0);
		s++;
	}
	return (1);
}

int	set_exit_status(char *str)
{
	int	i;

	if (!str)
		return (set_g_signal(0), 0);
	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]) && str[i] != ' ')
			return (set_g_signal(2), 0);
	}
	set_g_signal((int)ft_atoi(str));
	return (0);
}

int	hub_builtin(t_mini *mini, char *cmd, int pipefd[2])
{
	char	*pwd;

	if (!ft_strncmp("exit", cmd, 4))
		return (cmd += 4, close_pipe(pipefd), set_exit_status(cmd),
			mini->close(mini, get_g_signal()), 1);
	if (!ft_strncmp("echo -", cmd, 6) && check_echo_option(cmd + 6, 'n'))
		return (cmd += 6, changec(cmd, "\x01\x02\x03\x04", " |<>"),
			putstrfd(skipc(&cmd, 'n'), pipefd[1]), close_pipe(pipefd), 1);
	if (!ft_strncmp("cd", cmd, 2))
		return (cmd += 2, is_raw_path(mini,
				changec(cmd, "\x01\x02\x03\x04", " |<>")), close_pipe(pipefd), 1);
	if (!ft_strncmp("pwd", cmd, 3))
		return (pwd = getcwd(NULL, 0), putstrfd(pwd, pipefd[1]), free(pwd),
			putstrfd("\n", pipefd[1]), close_pipe(pipefd), 1);
	if (!ft_strncmp("export", cmd, 6))
		return (cmd += 7,
			handle_export(mini, changec(cmd, "\x01\x02\x03\x04", " |<>"), pipefd[1]),
			close_pipe(pipefd), 1);
	if (!ft_strncmp("unset", cmd, 5))
		return (cmd += 6,
			del_var_envpl(mini, changec(cmd, "\x01\x02\x03\x04", " |<>")),
			close_pipe(pipefd), 1);
	if (!ft_strncmp("env\0", cmd, 4))
		return (print_envpl(pipefd[1], mini), close_pipe(pipefd), 1);
	return (0);
}

void	handle_export(t_mini *mini, char *cmd, int fd)
{
	char	**exs;
	char	*varname;
	char	*varlue;
	int		i;	

	if (!*cmd)
		return (print_envpl(fd, mini));
	exs = ft_split(mini->solib, cmd, ' ');
	i = -1;
	while (exs[++i])
	{
		varlue = ft_substr(NULL,
				exs[i], get_c(exs[i], '=') + 1, ft_strlen(exs[i]));
		varname = ft_substr(NULL, exs[i], 0, get_c(exs[i], '='));
		set_envpl_var(mini, add_c_end(mini->solib, &varname, '='), varlue);
		free(varname);
		free(varlue);
	}
}
