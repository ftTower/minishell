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
#include <sotypes/soprintf.h>
#include <solibft/sostdlib.h>
#include <solibft/sostring.h>

volatile sig_atomic_t	g_signal;

void	stop_child_process(int code)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, WNOHANG);
	while (pid > 0)
    {
    	if (code == SIGINT)
			kill(pid, SIGTERM);
		else
			kill(pid, SIGQUIT);
		pid = waitpid(-1, &status, WNOHANG);
    }
}

void	ft_sig_quit(int id)
{
	soprintf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	if (id)
		kill(0, SIGQUIT);
	rl_redisplay();
}

void	ft_sig_segv(void)
{
	soprintf("Segmentation fault\n");
	exit(11);
}

static void	handle_signals(int code)
{
	stop_child_process(code);
	g_signal = 128 + code;
	soprintf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	/*if (code == SIGINT)
		ft_sig_quit(0);
	if (code == SIGQUIT)
		ft_sig_quit(1);
	if (code == SIGABRT)
		soprintf("abort\n");
	if (code == SIGSEGV)
		ft_sig_segv();*/
}

void mini_line_handler(t_mini *mini, char *line)
{
	if (*line)
		add_history(line);
	if (line && *line)
		mini_parsing(mini, line);
}

int minishell(t_solib *solib)
{
	t_mini	*mini;
	char	*shlvl;

	mini = minit(solib);
	signal(SIGINT, &handle_signals);
	signal(SIGSEGV, &handle_signals);
	signal(SIGABRT, &handle_signals);
	signal(SIGQUIT, &handle_signals);
	g_signal = 0;
	pre_parsing(mini);
	shlvl = soprintf_get(solib, "%d", (int)ft_atoi(get_envpl_var(mini, "SHLVL")) + 1);
	replace_envpl_var(mini, "SHLVL=", shlvl);
	rl_initialize();
	while (mini->loop)
		mini_line_handler(mini, readline(display_prompt(mini)));
	rl_clear_history();
	shlvl = soprintf_get(solib, "%d", ft_atoi(get_envpl_var(mini, "SHLVL")) - 1);
	replace_envpl_var(mini, "SHLVL=", shlvl);
	return (mini->close(mini, EXIT_SUCCESS));
}