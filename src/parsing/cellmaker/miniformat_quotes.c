/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniformat_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 23:37:13 by tauer             #+#    #+#             */
/*   Updated: 2024/08/08 01:19:23 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/all.h>

// void	t_char_list_handle_in_quotes(t_mini *mini, t_char **list)
// {
// 	t_char *current;

// 	current = *list;
// 	while(current)
// 	{
// 		if (current->type_quotes == TYP)
// 		current = current->next;
// 	}
// }

bool	t_char_list_format_quotes(t_mini *mini, t_char **list)
{
	t_char_set_pos(*list);
	t_char_identify_typequote(*list);
	return (t_char_print_typequote(mini, *list),false);
}