/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: almounib <almounib@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/04/11 21:31:29 by marvin            #+#    #+#             */
/*   Updated: 2024/05/20 17:40:22 by almounib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/all.h>
#include <solibft/sostdlib.h>
#include <solibft/sostring.h>
#include <sotypes/soprintf.h>

volatile sig_atomic_t	g_signal;

void	redisplay_prompt(void)
{
	soprintf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	stop_child_process(int code)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, 0);
	if (pid < 1)
		redisplay_prompt();
	else
		soprintf("\n");
	while (pid > 0)
	{
		if (code == SIGINT)
			kill(pid, SIGTERM);
		else
			kill(pid, SIGQUIT);
		pid = waitpid(-1, &status, WNOHANG);
	}
}

static void	handle_signals(int code)
{
	g_signal = 128 + code;
	stop_child_process(code);
}

void	mini_line_handler(t_mini *mini, char *line)
{
	if (!line)
		return (free(line), soprintf("exit\n"), (void)mini->close(mini, g_signal));
    if (!*line)
        return ;
    add_history(line);
	mini_parsing(mini, line);
    free(line);
}

int	minishell(t_solib *solib)
{
	t_mini	*mini;
	char	*shlvl;

	mini = minit(solib);
	signal(SIGINT, &handle_signals);
	signal(SIGQUIT, &handle_signals);
	g_signal = 0;
	shlvl = soprintf_get(solib, "%d", (int)ft_atoi(get_envpl_var(mini, "SHLVL"))
			+ 1);
	replace_envpl_var(mini, "SHLVL=", shlvl);
	rl_initialize();
	while (mini->loop)
		mini_line_handler(mini, readline(display_prompt(mini)));
    rl_clear_history();
	shlvl = soprintf_get(solib, "%d", ft_atoi(get_envpl_var(mini, "SHLVL"))
			- 1);
	replace_envpl_var(mini, "SHLVL=", shlvl);
	return (mini->close(mini, EXIT_SUCCESS));
}
