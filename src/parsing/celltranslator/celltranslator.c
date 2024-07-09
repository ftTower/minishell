/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/06/05 18:08:01 by marvin            #+#    #+#             */
/*   Updated: 2024/06/05 18:08:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/all.h>

bool	t_word_list_has_type(t_word *words, t_type type)
{
	t_word *current;

	current = words;
	while (current)
	{
		if (current->type == type)
			return (true);
		current = current->next;
	}
	return (false);
}

char	*string_constructor_t_word_list(t_mini *mini, t_word *word)
{
	t_word *current;
	char *new_word;
	char *ret;

	new_word = NULL;
	ret = NULL;
	current = word;
	while (current)
	{
		new_word = string_constructor(mini, current->c);
		ret = mini->libft->strjoin(mini->solib, ret, new_word);
		mini->print("%s\n", new_word);
		ret = mini->libft->strjoin(mini->solib, ret, ";");
		free(new_word);
		current = current->next;
	}
	return (ret);
}

t_pipex	*cell_pipex_builder(t_mini *mini, t_cell *cell)
{
	t_pipex *ret;
	t_word *cmd_line;
	t_word *current;
	ssize_t index;

	ret = mini->malloc(mini, sizeof(t_pipex));
	ret->args = NULL;
	ret->in_fd = NULL;
	ret->next = NULL;
	ret->out_fd = NULL;
	index = -1;
	cmd_line = NULL;
	while(++index < cell->nb_pipes)
	{
		current = cell->pipes[index].words;
		while(current)
		{
			word_add_back(mini, &cmd_line, current->refined_word);
			current = current->next;
		}
	}
	current = cmd_line;
	while(current)
	{
		print_t_word(mini, current);
		current = current->next;
	}
	return (ret);
}

void	print_t_pipex(t_mini *mini, t_pipex *pipex)
{
	ssize_t index;

	index = -1;
	if (!pipex || !pipex->args)
		return ;
	while (pipex->args[++index])
		mini->print("%s\n", pipex->args[index]);
}

bool	cell_translator(t_mini *mini, t_cell *cell)
{
	print_t_pipex(mini, cell_pipex_builder(mini, cell));
	return (false);
}
