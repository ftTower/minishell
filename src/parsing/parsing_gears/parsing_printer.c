/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_printer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/07/09 02:37:02 by tauer             #+#    #+#             */
/*   Updated: 2024/09/19 17:45:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/all.h>

void	print_t_type(t_mini *mini, t_type type)
{
	if (type == CMD_TYPE)
		mini->print("[CMD]");
	else if (type == BUILT_IN_TYPE)
		mini->print("[BUILT IN]");
	else if (type == PARA_TYPE)
		mini->print("[PARA]");
	else if (type == ARG_TYPE)
		mini->print("[ARG]");
	else if (type == REPLACE_IN_FD_TYPE || type == REPLACE_OUT_FD_TYPE)
		mini->print("[RE FD]");
	else if (type == CONCATE_IN_FD_TYPE || type == CONCATE_OUT_FD_TYPE)
		mini->print("[CONC FD]");
	else
		mini->print("[DEFAULT]");
}

void	print_t_word_list(t_mini *mini, t_word *word)
{
	t_word	*current;

	if (!word)
		return ((void)mini->print("empty"));
	current = word;
	while (current)
	{
		print_t_word(mini, current);
		current = current->next;
	}
}

void	print_t_word_list_double_quotes(t_mini *mini, t_char *word)
{
	if (!word)
		return ((void)mini->print("empty"));
	t_char_print_typequote(mini, word);
}

void	print_t_pipex_list(t_mini *mini, t_pipex *pipex)
{
	t_pipex	*current;
	ssize_t	index;

	index = -1;
	mini->print("\n\t╭─%Cff0000([)%Cf1c40f(%C5dade2(PIPEX LINE))%Cff0000(])\n\t|\n");
	current = pipex;
	while (current)
	{
		if (current->next)
			mini->print("\t├──");
		else
			mini->print("\t╰──");
		print_t_pipex(mini, current, ++index);
		current = current->next;
	}
}

void	print_envpl(int fd, t_mini *mini)
{
	t_envpl	*current;

	soprintf_fd(fd, "\n");
	current = mini->envpl;
	while (current)
	{
		soprintf_fd(fd, "%s\n", current->var);
		current = current->next;
	}
}
