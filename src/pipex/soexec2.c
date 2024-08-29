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



int	hub_builtin(t_mini *mini, char *cmd, int pipefd[2])
{
	if (!ft_strncmp("echo -n", cmd, 7))
	{
		write(1, "echo -n", 7);
		write(pipefd[1], "echo -n", 7);
		return (1);
	}
	if (!ft_strncmp("cd", cmd, 2))
		return (is_raw_path(mini, cmd + 3), 1);
	if (!ft_strncmp("pwd", cmd, 3))
	{
		putstrfd(get_envpl_var(mini, "PWD="), 1);
		putstrfd(get_envpl_var(mini, "PWD="), pipefd[1]);

		return (1);
	}
	return (0);
}

int	exec_fork_child(t_mini *mini, int pipefd[2], int filefd[2], char *command)
{
	int	ret;

	if (hub_builtin(command, pipefd))
		return (0);
	dup2(pipefd[0], 0);
	dup2(pipefd[1], 1);
	close(pipefd[0]);
	close(pipefd[1]);
	close(filefd[0]);
	close(filefd[1]);
	ret = str_exec(solib, command);
	solib->close(solib, EXIT_FAILURE);
	return (ret);
}

int	exec_fork(t_mini *mini, char *command, int pipefd[2], int filefd[2])
{
	int	pid;

	pid = fork();
	if (pid == -1)
		solib->close(solib, EXIT_FAILURE);
	if (pid == 0)
		exit(exec_fork_child(solib, pipefd, filefd, command));
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
		exec_fork(solib, commands[i], pipefd, filefd);
		if (pipe(pipefd) == -1)
			solib->close(solib, EXIT_FAILURE);
		pipe_swap(pipefd, filefd);
		i++;
	}
	close(pipefd[1]);
	close(filefd[0]);
	pipefd[1] = filefd[1];
	exec_fork(solib, commands[i], pipefd, filefd);
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
	if (pipe(pipefd) == -1)
		solib->close(solib, EXIT_FAILURE);
	pipe_swap(pipefd, filefd);
	return (strs_cmds(solib, commands, pipefd, filefd));
}
