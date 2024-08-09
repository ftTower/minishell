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

void	print_error_list(t_mini *mini, t_error_list *error_list)
{
	t_error_list *current;

	current = error_list;
	while (current)
	{
		mini->print("%d\n", current->error_code);
		current = current->next;
	}
}

void	add_error_to_list(t_mini *mini, t_error_list **error_list,
		t_error_code code)
{
	t_error_list *new_error;
	t_error_list *current;

	new_error = mini->malloc(mini, sizeof(t_error_list));
	new_error->error_code = code;
	new_error->next = NULL;
	if (!error_list || !*error_list)
		return (*error_list = new_error, (void)0);
	current = *error_list;
	while (current->next)
		current = current->next;
	return (current->next = new_error, (void)0);
}