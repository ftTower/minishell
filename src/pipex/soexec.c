/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/04/07 20:22:09 by marvin            #+#    #+#             */
/*   Updated: 2024/04/07 20:22:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/all.h>


int	ft_strarrfree(t_solib *solib, char **strarr)
{
	int k;

	k = -1;
	while (strarr[++k])
		solib->free(solib, strarr[k]);
	solib->free(solib, strarr);
	return (1);
}

static char	*strarr_prefixchr(t_solib *solib, char **strarr, char *target)
{
	while (*strarr && solib->libft->strncmp(target, *strarr,
			solib->libft->strlen(target)))
		strarr++;
	return (*strarr);
}

static char	*get_cmd(t_solib *solib, char **paths, char *cmd)
{
	char *temp;
	char *out;

	if (access(cmd, 0) == 0)
		return (cmd);
	while (*paths)
	{
		temp = solib->libft->strjoin(solib, *paths, "/");
		out = solib->libft->strjoin(solib, temp, cmd);
		solib->free(solib, temp);
		if (access(out, 0) == 0)
			return (out);
		solib->free(solib, out);
		paths++;
	}
	temp = solib->libft->strjoin(solib, "pipex: ", cmd);
	out = solib->libft->strjoin(solib, temp, ": command not found\n");
	write(2, out, solib->libft->strlen(out));
	solib->free(solib, out);
	solib->free(solib, temp);
	return (0);
}

void	putstrfd(char *str, int fd)
{
	ssize_t index;

	if (!str || fd < 0)
		return ;
	index = -1;
	while(str[++index])
		write(fd, &str[index], 1);
}

void	echon(char *str, int fd)
{
	putstrfd(str, fd);
}

void	pwd(t_mini *mini, int fd)
{
	putstrfd(get_envpl_var(mini, "PWD"), fd);
	putstrfd("\n", fd);
}

void	unset(t_mini *mini, char *var_to_unset, int fd)
{
	del_var_envpl(mini, var_to_unset);
	putstrfd("unset ", fd);
	putstrfd(var_to_unset, fd);
	putstrfd("\n", fd);
}



int	str_exec(t_solib *solib, char *str)
{
	static char **paths = 0;
	char *path;
	char **argv;
	char *cmd;
	int ret;

	path = strarr_prefixchr(solib, solib->env->envp, "PATH");
	if (!path)
		return (1);
	paths = solib->libft->split(solib, path + 5, ':');
	if (!paths)
		return (1);
	argv = solib->libft->split(solib, str, ' ');
	if (!argv && ft_strarrfree(solib, paths))
		return (1);
	cmd = get_cmd(solib, paths, argv[0]);
	ft_strarrfree(solib, paths);
	if (!cmd && ft_strarrfree(solib, argv))
		return (1);
	ret = execve(cmd, argv, solib->env->envp);
	solib->free(solib, cmd);
	ft_strarrfree(solib, argv);
	return (ret);
}
