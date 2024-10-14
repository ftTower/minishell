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

bool	cell_pipe_maker(t_mini *mini, t_pipe *pipe, char **pipe_words,
		ssize_t pipe_pos)
{
	pipe->words = NULL;
	pipe->fds = NULL;
	pipe->raw_words = NULL;
	pipe->used = false;
	pipe->pos = pipe_pos;
	if (!pipe_words || !*pipe_words || mini_formater(mini, pipe, pipe_words))
		return (true);
	return (false);
}

void	char_bool_quotes_switcher(char c, bool *single, bool *double_)
{
	if (c == '"')
	{
		if (!*double_)
			*double_ = true;
		else
			*double_ = false;
	}
	else if (c == (char)39)
	{
		if (!*single)
			*single = true;
		else
			*single = false;
	}
}

void	handle_negative_char_in_quotes( char *line, char space_replace,
			char pipe_replace)
{
	ssize_t	index;
	bool	double_quotes;
	bool	single_quotes;

	double_quotes = false;
	single_quotes = false;
	index = -1;
	while (line[++index])
	{
		char_bool_quotes_switcher(line[index], &single_quotes, &double_quotes);
		if ((double_quotes || single_quotes) && line[index] == ' ')
			line[index] = space_replace;
		else if ((double_quotes || single_quotes) && line[index] == '|')
			line[index] = pipe_replace;
	}
}

bool	cell_maker(t_mini *mini, t_cell *cell, char *raw_line)
{
	ssize_t	size;
	char	**lines;

	// 1. Manipule une copie de raw_line pour éviter de corrompre l'originale.
	char *transformed_line = mini->libft->strdup(NULL, raw_line);
	if (!transformed_line)
		return ( true);

	// 2. Remplace les espaces et pipes dans les guillemets
	handle_negative_char_in_quotes(transformed_line, '\x01', '\x02'); // remplace les espaces et pipes dans les quotes

	// 3. Vérifie la validité de la ligne après transformation
	if (!transformed_line || !*transformed_line || cells_empty_char(transformed_line, '|'))
	{
		free(transformed_line);
		return (handle_error(mini, raw_line, ERROR_EMPTY_PIPE), true);
	}

	// 4. Split la ligne transformée
	lines = mini->libft->split(mini->solib, transformed_line, '|'); // split sur les pipes
	if (strtlen(lines, &size))
	{
		free(transformed_line);
		return (true);
	}
	
	cell->nb_pipes = size;
	cell->final_line = NULL;
	cell->pipes = mini->malloc(mini, sizeof(t_pipe) * size);
	if (!cell->pipes)
	{
		free(transformed_line);
		return (true);
	}

	// 5. Pour chaque ligne, traite-la correctement et restaure les caractères remplacés.
	size = -1;
	while (lines[++size])
	{
		// 6. Remplace les caractères temporaires \x01 et \x02 par ' ' et '|' dans chaque sous-ligne
		// handle_negative_char_in_quotes(lines[size], ' ', '|');

		// 7. Split chaque sous-ligne sur les espaces
		if (cell_pipe_maker(mini, &cell->pipes[size],
				mini->libft->split(mini->solib, lines[size], ' '), size))
		{
			free(transformed_line);
			return (true);
		}
	}

	// Libère la mémoire allouée pour la ligne transformée
	free(transformed_line);
	return (false);
}

