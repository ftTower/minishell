/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:08:01 by marvin            #+#    #+#             */
/*   Updated: 2024/06/05 18:08:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/all.h>

bool	string_builder(t_mini *mini, t_pipe *pipe, char **pipe_words)
{
	if (t_char_list_maker(mini, &pipe->raw_words, pipe_words)
		|| redirect_unspacer(mini, pipe) || invalid_redirect(mini,
			&pipe->raw_words))
		return (mini->print("failed to build string\n"), true);
	return (false);
}
