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


int	hear_in(char *limiter)
{
	char	*doc;
	char	*line;
	char	*buf;
	int		pipefd[2];
	int		count;

	doc = malloc(sizeof(0));
	line = malloc(sizeof(0));
	buf = malloc(sizeof(1));
	count = 0;
	if (pipe(pipefd) == -1)
		return (-1);
	// soprintf("%d~>:", count);
	while (read(0, buf, 1))
	{
		ft_strmcat(NULL, &line, buf);
		if (*buf == '\n')
		{
			// printf("line : %s | limiter : %s\n", line, limiter);
			if (!ft_strncmp(line , limiter, ft_strlen(limiter) - 1))
				break;
			ft_strmcat(NULL, &doc, line);
			free(line);
			line = malloc(sizeof(0));
			count++;
			// soprintf("%d~>:", count);
		}
	}
	free(line);
	write(pipefd[1], doc, ft_strlen(doc));
	close(pipefd[1]);
	return (pipefd[0]);
}

int	hear_doc(char *path_in, char *path_out, int *in, int *out)
{
	soprintf("%s -- %s\n", path_in, path_out);
	if (!ft_strncmp("<<", path_in, 2))
		*in = hear_in(path_in + 2);
	else
		*in = open(path_in, O_RDONLY, 0644);
	if (*in < 0)
	{
		perror("Open");
		*in = open("/dev/null", O_RDONLY, 0644);
		if (*in < 0)
			return (1);
	}
	if (!ft_strncmp(">>", path_in, 2))
		*out = open(path_out + 2, O_WRONLY | O_CREAT, 0644);
	else
		*out = open(path_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*out < 0)
		return (1);
	return (0);
}

int	pipex(t_mini *mini, char *infile, char **commands, char *outfile)
{
	int	fdin;
	int	fdout;

	fdin = 0;
	fdout = 0;
	if (hear_doc(infile, outfile, &fdin, &fdout))
		return (perror("Open"), 1);
	return (strs_exec(mini, fdin, commands, fdout));
	return 0;
}
