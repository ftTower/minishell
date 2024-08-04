/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/04/07 20:22:15 by marvin            #+#    #+#             */
/*   Updated: 2024/04/07 20:22:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <minishell/all.h>

//! cell maker
//? cell_maker
bool	cell_pipe_maker(t_mini *mini, t_pipe *pipe, char **pipe_words,
		ssize_t pipe_pos);
bool	cell_maker(t_mini *mini, t_cell *cell, char *raw_line);
//? miniformat quotes
bool	handle_in_quotes(t_mini *mini, t_char **list);
bool	t_char_list_format_quotes(t_mini *mini, t_char **list);
//? miniformater
bool	redirect_unspacer(t_mini *mini, t_char **dst);
bool	mini_formater(t_mini *mini, t_pipe *pipe, char **pipe_words);
//! cell parser
//? cell_fd
bool	open_fd(t_mini *mini, t_word *word);
bool	fd_parser(t_mini *mini, t_word **dst);
bool	t_cell_connect_fd(t_mini *mini, t_cell *cell);
//? cell_variable
bool	t_word_variable_handler(t_mini *mini, t_word *word);
bool	t_pipe_variable_handler(t_mini *mini, t_pipe *pipe);
//? cell_parser
bool	t_pipe_parser(t_mini *mini, t_pipe *pipe, ssize_t pipe_pos);
bool	cell_parser(t_mini *mini, t_cell *cell);
//? type_parse
bool	t_word_parse_cmd(t_mini *mini, t_word *word);
bool	t_word_parse_redirect(t_word *word);
bool	t_word_parse_para(t_word *word);
bool	t_word_parse_type(t_mini *mini, t_word *word);
bool	t_pipe_parse_type(t_mini *mini, t_pipe *pipe);
//! cell translator
//?cell_translator
void	t_pipex_fill_in_fd(t_mini *mini, t_cell *cell, t_pipex *ret,
		ssize_t index);
bool	t_pipex_fill_out_ft(t_mini *mini, t_cell *cell, t_pipex *ret,
		ssize_t index);
t_pipex	*t_pipex_fill(t_mini *mini, t_cell *cell, t_pipex *ret);
bool	is_unused_t_pipe_in_cell(t_cell *cell);
bool	cell_translator(t_mini *mini, t_cell *cell);
//! envpl
//?envpl
char	*get_envpl_var(t_mini *mini, char *name_var);
bool	add_var_envpl(t_mini *mini, t_envpl **envpl, char *var);
bool	copy_envp_to_list(t_mini *mini);
void	variable_content_setter(t_mini *mini, t_char **dst, char *content);
char	*variable_content_getter(t_mini *mini, t_char **dst);
//! list_gears
//?t_char_list
bool	char_add_back(t_mini *mini, t_word *word, char c);
bool	char_t_char_add_back(t_mini *mini, t_char **list, char c);
bool	strr_to_t_char_list(t_mini *mini, t_char **dst, char **src);
void	t_char_set_pos(t_char *list);
bool	t_char_add_pos(t_mini *mini, t_char **dst, size_t pos, char c);
bool	t_char_del_pos(t_mini *mini, t_char **list, size_t pos_to_del);
//?t_pipex
bool	t_pipex_add_back(t_pipex **dst, t_pipex *src);
t_pipex	*new_t_pipex(t_mini *mini);
//?t_word_list
bool	word_add_back(t_mini *mini, t_word **words_list, char *word);
bool	t_word_list_add_back(t_mini *mini, t_word **dst, t_word *src);
bool	delete_word_in_list(t_mini *mini, t_word **words_list, t_word *word);
bool	t_word_list_has_type(t_word *words, t_type type);
t_word	*t_word_list_get_type(t_word **dst, t_type to_get);
//! parsing gears
//?parsing_debug
void	print_t_char_list(t_mini *mini, t_char *list);
void	print_double_tab(t_mini *mini, char **tab);
//?parsing_error
bool	cells_empty_char(t_mini *mini, char *raw_line, char c);
bool	invalid_redirect(t_mini *mini, t_char **list);
//?parsing_printer
void	print_t_char(t_mini *mini, t_char *c, t_color color);
void	print_t_word(t_mini *mini, t_word *word);
void	print_t_word_list(t_mini *mini, t_word *word);
void	print_t_pipe(t_mini *mini, t_pipe *pipe);
void	print_t_pipex(t_mini *mini, t_pipex *pipex, ssize_t pos);
void	print_t_pipex_list(t_mini *mini, t_pipex *pipex);
void	print_t_cell(t_mini *mini, t_cell *cell);
void	print_envpl(t_mini *mini);
//?parsing_utils
bool	strtlen(char **tab, ssize_t *ret);
void	free_tab(char **tab);
//! string_gears
//?string_gears
char	*t_char_list_to_str(t_mini *mini, t_char *list);
char	*t_word_to_str(t_mini *mini, t_word *word);
char	*t_word_list_to_str(t_mini *mini, t_word *word);

//! parsing
bool	mini_parsing(t_mini *mini, char *line);

#endif
