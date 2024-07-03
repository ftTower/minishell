/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 20:22:15 by marvin            #+#    #+#             */
/*   Updated: 2024/04/07 20:22:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CELLS_H
# define CELLS_H

# include <minishell/all.h>

// cells
bool cells_handler(t_mini *mini, char *line, size_t pos);

// pipes
bool	pipe_maker(t_mini *mini, t_pipe *pipe, char **pipe_words);

//words
bool	word_add_back(t_mini *mini, t_word **words_list, char *word);

//chars
bool	char_add_back(t_mini *mini, t_word *word, char c);

//error 
bool	cells_empty_pipe(t_mini *mini, char *raw_line);

//print
void	print_double_tab(t_mini *mini, char **tab);
void	print_t_char(t_mini *mini, t_char *c, bool lignfeed);
void	print_t_word(t_mini *mini, t_word *word);
void	print_t_pipe(t_mini *mini, t_pipe *pipe);

//utils
bool	strtlen(char **tab, ssize_t *ret);

#endif
