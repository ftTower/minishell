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

#ifndef PARSING_H
# define PARSING_H

# include <minishell/all.h>

//cell translator
bool	cell_translator(t_mini *mini, t_cell *cell);

//cell parser
bool	cell_parser(t_mini *mini, t_cell *cell);

//envpl
bool	copy_envp_to_list(t_mini *mini);
bool	add_var_envpl(t_mini *mini, t_envpl **envpl, char *var);
void	print_envpl(t_mini *mini);
char	*get_envpl_var(t_mini *mini, char *name_var);

//string builder gears
bool	strr_to_t_char_list(t_mini *mini, t_char **dst, char **src);
char	*string_constructor(t_mini *mini, t_char *list);

//string builder redirect
bool	redirect_unspacer(t_mini *mini, t_char **list);
bool	invalid_redirect(t_mini *mini, t_char **list);

//string builder
bool	string_formater(t_mini *mini, t_pipe *pipe, char **pipe_words);

// cells
bool cells_handler(t_mini *mini, char *line, size_t pos);
bool   mini_parsing(t_mini *mini, char *line);
bool	cell_maker(t_mini *mini, t_cell *cell, char *raw_line);

// pipes
bool	pipe_maker(t_mini *mini, t_pipe *pipe, char **pipe_words);
bool	pipe_parser(t_mini *mini, t_pipe *pipe, ssize_t pipe_pos);


//words
bool	word_copy_back(t_mini *mini, t_word **words_list, t_word *word);
bool	word_add_back(t_mini *mini, t_word **words_list, char *word);
bool	word_char_indexer(t_word *word);
bool	word_parser(t_mini *mini, t_pipe *pipe, t_word *word, ssize_t word_pos);

//chars
bool	char_add_back(t_mini *mini, t_word *word, char c);
bool	char_t_char_add_back(t_mini *mini, t_char **list, char c);
bool	char_t_char_del_pos(t_mini *mini, t_char **list, ssize_t pos);

//fds
bool	fd_getter(t_mini *mini, t_char *current, t_pipe *pipe);
bool	fd_watcher(t_mini *mini, t_word *word, t_pipe *pipe);

//error 
bool	cells_empty_char(t_mini *mini, char *raw_line, char c);

//print
void	print_double_tab(t_mini *mini, char **tab);
void	print_t_char(t_mini *mini, t_char *c, t_color color);
void	print_t_char_list(t_mini *mini, t_char *list);
void	print_t_word(t_mini *mini, t_word *word);
void	print_t_pipe(t_mini *mini, t_pipe *pipe);
void	print_t_cell(t_mini *mini, t_cell *cell);

//utils
bool	strtlen(char **tab, ssize_t *ret);


bool	mini_formater(t_mini *mini, t_pipe *pipe, char **pipe_words);
bool	t_pipe_parse_type(t_mini *mini, t_pipe *pipe);
void	free_tab(char **tab);

#endif
