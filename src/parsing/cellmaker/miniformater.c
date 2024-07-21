/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniformater.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 02:13:56 by tauer             #+#    #+#             */
/*   Updated: 2024/07/21 17:28:25 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/all.h>

bool	redirect_unspacer(t_mini *mini, t_char **dst)
{
	t_char	*current;
	t_char	*tmp;

	current = (*dst);
	while (current)
	{
		if ((current->c == '<' || current->c == '>') && current->next
			&& (current->next->c == ' '))
		{
			tmp = current->next;
			current->next = current->next->next;
			mini->free(mini, tmp);
		}
		if ((current->c == '<' || current->c == '>') && !current->next)
			return (mini->print("found empty redirect...\n"), true);
		current = current->next;
	}
	return (false);
}


char *variable_content_getter(t_mini *mini, t_char **dst)
{
	t_word *variable_name;
	t_char *current;

	variable_name = mini->malloc(mini, sizeof(t_word));
	variable_name->c = NULL;
	variable_name->next = NULL;
	current = (*dst);
	while(current && current->c != ' ')
	{
		if (current->c != '$')
			char_add_back(mini, variable_name, current->c);	
		current = current->next;
	}
	return (get_envpl_var(mini, t_word_list_to_str(mini, variable_name)));
}

bool	variable_setter(t_mini *mini, t_char **dst)
{
	mini->print("((%s))\n", variable_content_getter(mini, dst));
	return (false);
}

bool	variable_handler(t_mini *mini, t_char **dst)
{
	t_char *current;

	current = (*dst);
	while(current)
	{
		if (current->c == '$' && !current->next)
			return (mini->print("empty $variable\n"), true);
		else if (current->c == '$' && current->next)
			variable_setter(mini, &current);
		current = current->next;
	}
	return (false);
}

bool	mini_formater(t_mini *mini, t_pipe *pipe, char **pipe_words)
{
	if (strr_to_t_char_list(mini, &pipe->raw_words, pipe_words)
		|| redirect_unspacer(mini, &pipe->raw_words) || invalid_redirect(mini,
			&pipe->raw_words) || variable_handler(mini, &pipe->raw_words))
		return (mini->print("failed to build string\n"), true);
	return (print_t_char_list(mini, pipe->raw_words),false);
}
