/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 20:22:15 by marvin            #+#    #+#             */
/*   Updated: 2024/04/07 20:22:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <minishell/all.h>

int		hub_builtin(t_mini *mini, char *cmd, int pipefd[2]);
int		str_exec(t_mini *mini, char *str);
int		strs_exec(t_mini *mini, int fdin, char **commands, int fdout);
int		pipex(t_mini *mini, char *infile, char **commands, char *outfile);
void	close_pipe(int pipefd[2]);
void	handle_export(t_mini *mini, char *cmd, int fd);
char	**format_cmds(t_mini *mini, char *str);

#endif
