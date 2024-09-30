#include <minishell/all.h>

bool	open_fd(t_mini *mini, t_word *word)
{
	int	fd;

	if (word->type == REPLACE_IN_FD_TYPE || word->type == REPLACE_OUT_FD_TYPE)
		word->refined_word = t_char_list_to_str(mini, word->c->next);
	else if (word->type == CONCATE_IN_FD_TYPE
		|| word->type == CONCATE_OUT_FD_TYPE)
		word->refined_word = t_char_list_to_str(mini, word->c->next->next);
	else
		return (mini->print("wrong type in open_fd\n"), false);
	if (word->type == REPLACE_IN_FD_TYPE || word->type == CONCATE_IN_FD_TYPE)
	{
		fd = open(word->refined_word, O_RDONLY);
		if (fd == -1)
			return (handle_error(mini, word->refined_word, ERROR_FAILED_OPEN_IN_FD), true);
		close(fd);
	}
	else if (word->type == REPLACE_OUT_FD_TYPE
		|| word->type == CONCATE_OUT_FD_TYPE)
	{
		fd = open(word->refined_word, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			return (handle_error(mini, word->refined_word, ERROR_FAILED_OPEN_OUT_FD), true);
		close(fd);
	}
	return (false);
}

bool	fd_parser(t_mini *mini, t_word **dst)
{
	t_word	*current;
	t_word	*next;

	current = *dst;
	while (current)
	{
		next = current->next;
		if (((current->type == REPLACE_IN_FD_TYPE
					|| current->type == CONCATE_IN_FD_TYPE)
				&& (t_word_list_has_type(current->next, REPLACE_IN_FD_TYPE)
					|| t_word_list_has_type(current->next, CONCATE_IN_FD_TYPE)))
			|| ((current->type == REPLACE_OUT_FD_TYPE
					|| current->type == CONCATE_OUT_FD_TYPE)
				&& (t_word_list_has_type(current->next, REPLACE_OUT_FD_TYPE)
					|| t_word_list_has_type(current->next,
						CONCATE_OUT_FD_TYPE))))
		{
			if (open_fd(mini, current))
				return (true);
			delete_word_in_list(mini, dst, current);
		}
		current = next;
	}
	return (false);
}

bool	t_cell_connect_fd(t_mini *mini, t_cell *cell)
{
	ssize_t index;

	index = -1;
	while (++index + 1 < cell->nb_pipes)
	{
		if (!t_word_list_has_type(cell->pipes[index].fds, REPLACE_OUT_FD_TYPE)
			&& !t_word_list_has_type(cell->pipes[index].fds,
				CONCATE_OUT_FD_TYPE) && (t_word_list_has_type(cell->pipes[index
					+ 1].fds, REPLACE_IN_FD_TYPE)
				|| t_word_list_has_type(cell->pipes[index + 1].fds,
					CONCATE_IN_FD_TYPE)))
			word_add_back(mini, &cell->pipes[index].fds, ">/dev/null");
		else if ((t_word_list_has_type(cell->pipes[index].fds,
					REPLACE_OUT_FD_TYPE)
				|| t_word_list_has_type(cell->pipes[index].fds,
					CONCATE_OUT_FD_TYPE))
			&& (!t_word_list_has_type(cell->pipes[index + 1].fds,
					REPLACE_IN_FD_TYPE)
				&& !t_word_list_has_type(cell->pipes[index + 1].fds,
					CONCATE_IN_FD_TYPE)))
			word_add_back(mini, &cell->pipes[index + 1].fds, "</dev/null");
	}
	return (false);
}
