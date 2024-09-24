#include <minishell/all.h>

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
