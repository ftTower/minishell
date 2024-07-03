/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 01:06:57 by tauer             #+#    #+#             */
/*   Updated: 2024/07/04 00:08:33 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/all.h>

// typedef struct s_pipe
// {
// 	t_word *words;
// } t_pipe;

// | echo "coucou" |
// | cat -e <infile>outfile |

bool	pipe_maker(t_mini *mini, t_pipe *pipe, char **pipe_words)
{
	ssize_t	index;

	pipe->words = NULL;
	index = -1;
	while (pipe_words[++index])
		word_add_back(mini, &pipe->words, pipe_words[index]);
	return (false);
}
