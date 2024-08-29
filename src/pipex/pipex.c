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

int	pipex_openfd(char *path_in, char *path_out, int *in, int *out)
{
	*in = open(path_in, O_RDONLY, 0644);
	if (*in < 0)
	{
		perror("Open");
		*in = open("/dev/null", O_RDONLY, 0644);
		if (*in < 0)
			return (1);
	}
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
	if (pipex_openfd(infile, outfile, &fdin, &fdout))
		return (perror("Open"), 1);
	return (strs_exec(mini, fdin, commands, fdout));
}
