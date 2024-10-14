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
#include <solibft/sostring.h>

int	ft_strarrfree(t_mini *mini, char **strarr)
{
	int	k;

	k = -1;
	while (strarr[++k])
		mini->free(mini, strarr[k]);
	mini->free(mini, strarr);
	return (1);
}

static char	*strarr_prefixchr(t_mini *mini, char **strarr, char *target)
{
	while (*strarr && mini->libft->strncmp(target, *strarr,
			mini->libft->strlen(target) - 1))
		strarr++;
	return (*strarr);
}

static char	*get_cmd(t_mini *mini, char **paths, char *cmd)
{
	char	*temp;
	char	*out;

	if (access(cmd, 0) == 0)
		return (cmd);
	while (*paths)
	{
		temp = mini->libft->strjoin(mini->solib, *paths, "/");
		out = mini->libft->strjoin(mini->solib, temp, cmd);
		mini->free(mini, temp);
		if (access(out, 0) == 0)
			return (out);
		mini->free(mini, out);
		paths++;
	}
	temp = mini->libft->strjoin(mini->solib, "pipex: ", cmd);
	out = mini->libft->strjoin(mini->solib, temp, ": command not found\n");
	write(2, out, mini->libft->strlen(out));
	mini->free(mini, out);
	mini->free(mini, temp);
	return (0);
}

char	**envpl_to_envp(t_mini *mini)
{
	char	**envp;
	t_envpl	*current;
	int		len;

	current = mini->envpl;
	len = 0;
	while (current)
	{
		len++;
		current = current->next;
	}
	current = mini->envpl;
	envp = somalloc(mini->solib, sizeof(char *) * (len + 1));
	envp[len] = NULL;
	len = 0;
	while (current)
	{
		envp[len] = ft_strdup(mini->solib, current->var);
		current = current->next;
		len++;
	}
	return (envp);
}

int	str_exec(t_mini *mini, char *str)
{
	static char	**paths = 0;
	char		*path;
	char		**argv;
	char		*cmd;
	int			ret;

	path = strarr_prefixchr(mini, mini->env->envp, "PATH");
	if (!path)
		return (1);
	paths = mini->libft->split(mini->solib, path + 5, ':');
	if (!paths)
		return (1);
	argv = format_cmds(mini, str);
	if (!argv && ft_strarrfree(mini, paths))
		return (1);
	cmd = get_cmd(mini, paths, argv[0]);
	ft_strarrfree(mini, paths);
	if (!cmd && ft_strarrfree(mini, argv))
		return (1);
	ret = execve(cmd, argv, envpl_to_envp(mini));
	mini->free(mini, cmd);
	ft_strarrfree(mini, argv);
	return (ret);
}
