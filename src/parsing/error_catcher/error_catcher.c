/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_catcher.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/08/09 20:26:30 by tauer             #+#    #+#             */
/*   Updated: 2024/08/09 20:26:30 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/all.h>


// t_error_code	get_error_codes(t_pipe *pipe)
// {
// }

void	error_empty_redirect(t_mini *mini, t_error_list *element)
{
	mini->print("Error: %s\n", element->content);
}

void	error_checkpoint(t_mini *mini, t_error_list *element)
{
	const char *colors[] = {
		"\033[48;5;196m",
		"\033[0m"
	};

	if (element->error_code == ERROR_CHECKPOINT_CELL_PIPE_MAKER)
		mini->print("%s[Error during formatting]%s", colors[0], colors[1]);		
	else if (element->error_code == ERROR_CHECKPOINT_CELL_PARSER)
		mini->print("%s[Error during parsing]%s", colors[0], colors[1]);		
}

void	selector(t_mini *mini, t_error_list *element)
{
	if (element->error_code == ERROR_CHECKPOINT_CELL_PIPE_MAKER
		|| element->error_code == ERROR_CHECKPOINT_CELL_PARSER)
		error_checkpoint(mini, element);
	else if (element->error_code == ERROR_EMPTY_REDIRECT)
		error_empty_redirect(mini, element);
	else
		mini->print("Error: %s\n", element->content);
}

void	handle_error(t_mini *mini, t_error_list *error_list)
{
	t_error_list *current;

	current = error_list;
	while (current)
	{
		selector(mini, current);
		current = current->next;
	}
}

void	print_error_list(t_mini *mini, t_error_list *error_list)
{
	t_error_list *current;

	current = error_list;
	while (current)
	{
		mini->print("%d - %s\n", current->error_code, current->content);
		current = current->next;
	}
}

void	add_error_to_list(t_mini *mini, t_error_list **error_list,
		t_error_code code, char *content)
{
	t_error_list *new_error;
	t_error_list *current;

	mini->print("%d - %s\n", code, content);
	new_error = mini->malloc(mini, sizeof(t_error_list));
	new_error->error_code = code;
	new_error->content = content;
	new_error->next = NULL;
	if (!error_list || !*error_list)
		return (*error_list = new_error, (void)0);
	current = *error_list;
	while (current->next)
		current = current->next;
	return (current->next = new_error, (void)0);
}