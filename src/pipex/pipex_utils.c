/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 21:58:21 by marvin            #+#    #+#             */
/*   Updated: 2024/10/14 21:58:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/all.h>
#include <solibft/sostring.h>

void	putstrfd(char *str, int fd)
{
	ssize_t	index;

	if (!str || fd < 0)
		return ;
	index = -1;
	while (str[++index])
		write(fd, &str[index], 1);
}

char	**format_cmds(t_mini *mini, char *str)
{
	char	**argv;
	int		i;

	argv = ft_split(mini->solib, str, ' ');
	i = -1;
	while (argv[++i])
		changec(argv[i], "\x01\x02\x03\x04", " |<>");
	return (argv);
}

void	close_pipe(int pipefd[2])
{
	if (!pipefd)
		return ;
	if (pipefd[0])	
		close(pipefd[0]);
	if (pipefd[1])
		close(pipefd[1]);
}
