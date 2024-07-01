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

void mini_line_handler(t_mini *mini, char *line)
{
	char **cells;
	ssize_t index;
	
	if (line && *line)
	{
		//mini->print("\n");
		cells = mini->libft->split(mini->solib, line, ';');
		index = -1;
		while(cells[++index])
			cells_handler(mini, cells[index]);
		
			
		//mini->print("\n");
	}
	mini->print("\n");
	if (!mini->libft->strncmp(line, "exit", 4))
		mini->loop = 0; // Condition de sortie de la boucle principale
	else
		mini_prompt();
}

int line_update(t_mini *mini, char *line, int key)
{
	(void)mini;
	(void)line;
	rl_insert_text((char *)&key);
	return (0);
}


void mini_special_keys(t_mini *mini, char *line, int key)
{
	if (key == '\n' || key == '\r')
	{
		mini_line_handler(mini, line);
		if (*line)
			add_history(line);
	}
	if (key == 127 && rl_point > 0)
	{
		if (rl_point == 1)
		{
			rl_delete_text(0 , 1);
			rl_redisplay();
			mini_prompt();
		}
		else if (rl_point > 1)
		{
			rl_delete_text(rl_point - 1, rl_point);
			rl_redisplay();
			rl_point--;
		}

	}
}

void mini_start(t_mini *mini)
{
	int	key;

	rl_callback_handler_install("", line_handler);
	mini_prompt();
	// Boucle principale
	while (mini->loop)
	{
		key = rl_read_key(); // Lecture d'une seule touche
		if (key >= 32 && key <= 126)
			line_update(mini, rl_line_buffer, key);
		else
			mini_special_keys(mini, rl_line_buffer, key);
		rl_redisplay();
	}
}

int minishell(t_solib *solib)
{
	t_mini *mini;

	mini = minit(solib);
	pre_parsing(mini);
	rl_initialize();
	mini_start(mini);
	return (mini->close(mini, EXIT_SUCCESS));
}