/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   soexec2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 22:00:43 by marvin            #+#    #+#             */
/*   Updated: 2024/05/27 22:00:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/all.h>
#include <solibft/sostring.h>

void	pipe_swap(int pipefd[2], int filefd[2])
{
	int	tmp;

	tmp = pipefd[0];
	pipefd[0] = filefd[0];
	filefd[0] = tmp;
}

void	close_pipe(int pipefd[2])
{
	close(pipefd[0]);
	close(pipefd[1]);
}

int	hub_builtin(t_mini *mini, char *cmd, int pipefd[2])
{
	if (!ft_strncmp("exit", cmd, 4))
		return (close_pipe(pipefd), mini->close(mini, EXIT_SUCCESS), 1);
	if (!ft_strncmp("echo -n", cmd, 7))
		return (putstrfd(cmd + 8, pipefd[1]), putstrfd("\n", pipefd[1]), close_pipe(pipefd), 1);
	if (!ft_strncmp("cd", cmd, 2))
		return (is_raw_path(mini, cmd + 3), close_pipe(pipefd), 1);
	if (!ft_strncmp("pwd", cmd, 3))
		return (putstrfd(get_envpl_var(mini, "PWD"), pipefd[1]),
			putstrfd("\n", pipefd[1]), close_pipe(pipefd), 1);
	if (!ft_strncmp("export", cmd, 6))
		return (close_pipe(pipefd), 1);
	if (!ft_strncmp("unset", cmd, 5))
		return (del_var_envpl(mini, cmd + 6), close_pipe(pipefd), 1);
	if (!ft_strncmp("env", cmd, 3))
		return (print_envpl(pipefd[1], mini), close_pipe(pipefd), 1);
	return (0);
}

int	exec_fork_child(t_mini *mini, int pipefd[2], int filefd[2], char *command)
{
	int	ret;

	if (hub_builtin(mini, command, pipefd))
		return (close_pipe(filefd), mini->solib->close(mini->solib, EXIT_SUCCESS));
	dup2(pipefd[0], 0);
	dup2(pipefd[1], 1);
	close_pipe(pipefd);
	close_pipe(filefd);
	ret = str_exec(mini, command);
	mini->solib->close(mini->solib, ret);
	return (ret);
}

int	exec_fork(t_mini *mini, char *command, int pipefd[2], int filefd[2])
{
	g_signal_pid  = fork();
	if (g_signal_pid  < 0)
		mini->solib->close(mini->solib, EXIT_FAILURE);
	if (!g_signal_pid)
		exit(exec_fork_child(mini, pipefd, filefd, command));
	close(pipefd[0]);
	close(pipefd[1]);
	return (0);
}

int	strs_cmds(t_mini *mini, char **commands, int pipefd[2], int filefd[2])
{
	int	i;
	int	status;

	i = 0;
	while (commands[i + 1])
	{
		exec_fork(mini, commands[i], pipefd, filefd);
		if (pipe(pipefd) == -1)
			mini->solib->close(mini->solib, EXIT_FAILURE);
		pipe_swap(pipefd, filefd);
		i++;
	}
	close(pipefd[1]);
	close(filefd[0]);
	pipefd[1] = filefd[1];
	exec_fork(mini, commands[i], pipefd, filefd);
	while (wait(&status) != -1)
		continue ;
	close(pipefd[0]);
	close(pipefd[1]);
	return (status);
}

int	strs_exec(t_mini *mini, int fdin, char **commands, int fdout)
{
	int		pipefd[2];
	int		filefd[2];

	if (!commands || !*commands)
		return (0);
	filefd[1] = fdout;
	filefd[0] = fdin;
	if (!commands[1] && hub_builtin(mini, *commands, filefd))
		return (0);
	if (pipe(pipefd) == -1)
		mini->solib->close(mini->solib, EXIT_FAILURE);
	pipe_swap(pipefd, filefd);
	return (strs_cmds(mini, commands, pipefd, filefd));
}
