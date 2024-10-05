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

int	exec_fork_child(t_mini *mini, int pipefd[2], int filefd[2], char *command)
{
	int	ret;

	if (hub_builtin(mini, command, pipefd))
		return (close_pipe(filefd),
			mini->solib->close(mini->solib, EXIT_SUCCESS));
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
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		mini->solib->close(mini->solib, EXIT_FAILURE);
	if (!pid)
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
    g_signal = 0;
	while (wait(&status) != -1)
	{
		if (WIFEXITED(status) && status)
        	g_signal = WEXITSTATUS(status);
    	if (WIFSIGNALED(status))
       		g_signal = WTERMSIG(status) + 128;
    }
	return (close_pipe(pipefd), status);
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

void	close_pipe(int pipefd[2])
{
	close(pipefd[0]);
	close(pipefd[1]);
}