/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 01:06:57 by tauer             #+#    #+#             */
/*   Updated: 2024/07/04 01:47:49 by tauer            ###   ########.fr       */
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

bool	pipe_parser(t_mini *mini, t_pipe *pipe, ssize_t pipe_pos)
{
	t_word *current;
	ssize_t word_pos;

	current = pipe->words;
	pipe->pos = pipe_pos;
	word_pos = 0;
	while (current)
	{
		if (word_parser(mini, pipe, current, word_pos++))
			return (true);
		current = current->next;
	}

	print_t_pipe(mini, pipe);
	return (false);
}
