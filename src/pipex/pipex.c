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

void	read_line_fd(int fd, char **doc, char **line, char *limiter)
{
	char	*buf;
	size_t	count;

	buf = ft_strdup(NULL, "0");
	count = 0;
	while (1)
	{
		soprintf("%d~>:", count);
		free(*line);
		*line = NULL;
		*line = ft_strdup(NULL, "");
		while (read(fd, buf, 1))
		{
			ft_strmcat(NULL, line, buf);
			if (*buf == '\n' || *buf == '\0')
				break ;
		}
		count += 1;
		if (!ft_strncmp(*line , limiter, ft_strlen(limiter)))
			break;
		ft_strmcat(NULL, doc, *line);
	}
	free(buf);
}

int	hear_in(char *limiter)
{
	char	*doc;
	char	*line;
	char	*new_limiter;
	int		pipefd[2];

	doc = ft_strdup(NULL, "");
	line = ft_strdup(NULL, "");
	new_limiter = ft_strjoin(NULL, limiter, "\n");
	if (pipe(pipefd) == -1)
		return (-1);
	read_line_fd(0, &doc, &line, new_limiter);
	write(pipefd[1], doc, ft_strlen(doc));
	close(pipefd[1]);
	free(doc);
	free(line);
	free(new_limiter);
	return (pipefd[0]);
}

int	heredoc(char *path_in, char *path_out, int *in, int *out)
{
	if (!ft_strncmp("<<", path_in, 2))
		*in = hear_in(path_in + 2);
	else if (!ft_strncmp("<", path_in, 1))
		*in = open(path_in + 1, O_RDONLY, 0644);
	else
		*in = open(path_in, O_RDONLY, 0644);
	if (*in < 0)
	{
		perror("Open in");
		*in = open("/dev/null", O_RDONLY, 0644);
		if (*in < 0)
			return (1);
	}
	if (!ft_strncmp(">>", path_out, 2))
		*out = open(path_out + 2, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (!ft_strncmp(">", path_out, 1))
		*out = open(path_out + 1, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		*out = open(path_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*out < 0)
		return (perror("Open out"), 1);
	return (0);
}


int	pipex(t_mini *mini, char *infile, char **commands, char *outfile)
{
	int	fdin;
	int	fdout;

	fdin = 0;
	
	fdout = 0;
	if (heredoc(infile, outfile, &fdin, &fdout))
		return (perror("Open"), 1);
	return (strs_exec(mini, fdin, commands, fdout));
	return 0;
}