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
	char *ret;
	t_word *current_word;
	t_char *current_char;
	ssize_t index;

	index = 0;
	current_word = word;
	while(current_word)
	{
		current_char = current_word->c;
		while(current_char)
		{
			++index;
			current_char = current_char->next;
		}
		current_word = current_word->next;
	}
	ret = mini->malloc(mini, sizeof(char) * (index + 1));
	index = 0;
	current_word = word;
	while(current_word)
	{
		current_char = current_word->c;
		while(current_char)
		{
			ret[index++] = current_char->c;
			current_char = current_char->next;
		}
		current_word = current_word->next;
	}
	return (ret[index] = '\0', ret);
}

char	*string_constructor_t_word(t_mini *mini, t_word *word)
{
	char *ret;
	t_char *current_char;
	ssize_t index;

	index = 0;
	current_char = word->c;
	while(current_char)
	{
		++index;
		current_char = current_char->next;
	}
	ret = mini->malloc(mini, sizeof(char) * (index + 1));
	index = 0;
	current_char = word->c;
	while(current_char)
	{
		ret[index++] = current_char->c;
		current_char = current_char->next;
	}
	return (ret[index] = '\0', ret);
}

bool	t_pipex_add_back(t_pipex **dst, t_pipex *src)
{
	t_pipex *current;

	current = *dst;
	if (!current)
		*dst = src;
	else
	{
		while(current->next)
			current = current->next;
		current->next = src;
	}
	return (false);
}

t_pipex *new_t_pipex(t_mini *mini)
{
	t_pipex *new;

	new = mini->malloc(mini, sizeof(t_pipex));
	new->args = NULL;
	new->in_fd = NULL;
	new->next = NULL;
	new->out_fd = NULL;
	return (new);
}

bool	t_word_list_add_back(t_mini *mini, t_word **dst, t_word *src)
{
	t_word *current;

	current = src;
	while(current)
	{
		word_add_back(mini, dst, current->refined_word);
		if (current->next)
			word_add_back(mini, dst, " ");
		current = current->next;
	}

	return (false);
}

t_word *t_word_list_get_type(t_word **dst, t_type to_get)
{
	t_word *current;
	t_word *ret;

	current = *dst;
	ret = NULL;
	while(current)
	{
		if (current->type == to_get)
		{
			ret = current;
			break;
		}
		current = current->next;
	}
	return (ret);
}

t_pipex	*cell_pipex_builder(t_mini *mini, t_cell *cell)
{
	t_pipex *ret;

	char *tmp;
	t_word *cmd_line;

	ssize_t index;

	ret = new_t_pipex(mini);
	tmp = NULL;
	index = -1;
	cmd_line = NULL;
	while(++index < cell->nb_pipes)
	{
		if (!cell->pipes[index].used)
		{
				cell->pipes[index].used = true;
				if (!cmd_line && (t_word_list_has_type(cell->pipes[index].fds, REPLACE_IN_FD_TYPE)))
					ret->in_fd = string_constructor_t_word(mini,t_word_list_get_type(&cell->pipes[index].fds, REPLACE_IN_FD_TYPE));
				else if (!cmd_line && (t_word_list_has_type(cell->pipes[index].fds, CONCATE_IN_FD_TYPE)))
					ret->in_fd = string_constructor_t_word(mini,t_word_list_get_type(&cell->pipes[index].fds, CONCATE_IN_FD_TYPE));
				t_word_list_add_back(mini, &cmd_line, cell->pipes[index].words);
				if (cell->pipes[index].fds && t_word_list_has_type(cell->pipes[index].fds, REPLACE_OUT_FD_TYPE))
				{
					ret->out_fd = string_constructor_t_word(mini, t_word_list_get_type(&cell->pipes[index].fds, REPLACE_OUT_FD_TYPE));
					break;
				}
				else if (cell->pipes[index].fds && t_word_list_has_type(cell->pipes[index].fds, CONCATE_OUT_FD_TYPE))
				{
					ret->out_fd = string_constructor_t_word(mini, t_word_list_get_type(&cell->pipes[index].fds, CONCATE_OUT_FD_TYPE));
					break;
				}
				else
				word_add_back(mini, &cmd_line, ";");
		}
	}
	tmp = string_constructor_t_word_list(mini, cmd_line);
	ret->args = mini->libft->split(mini->solib, tmp, ';');
	return (ret);
}

bool	is_unused_t_pipe_in_cell(t_cell *cell)
{
	ssize_t index;

	index = -1;
	while (++index < cell->nb_pipes)
	{
		if (!cell->pipes[index].used)
			return (true);
	}
	return (false);
}

void	print_t_pipex(t_mini *mini, t_pipex *pipex)
{
	ssize_t index;

	index = -1;
	if (!pipex || !pipex->args)
		return ;
	mini->print("\n[T_PIPEX_LINE]\t[%s] ", pipex->in_fd);
	while (pipex->args[++index])
		mini->print("[%s] ", pipex->args[index]);
	mini->print("[%s]\n", pipex->out_fd);
}



bool	cell_translator(t_mini *mini, t_cell *cell)
{
	t_pipex *current;

	cell->final_line = NULL;
	while(is_unused_t_pipe_in_cell(cell))
		t_pipex_add_back( &cell->final_line, cell_pipex_builder(mini, cell));
	current = cell->final_line;
	while(current)
	{
		print_t_pipex(mini, current);
		current = current->next;
	}
	return (false);
}
