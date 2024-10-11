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

//! cell exec
//? cell exec
bool	cell_pipex_exec(t_mini *mini, t_pipex *list);
//! cell maker
//? cell_maker
bool	cell_pipe_maker(t_mini *mini, t_pipe *pipe, char **pipe_words,
			ssize_t pipe_pos);
bool	cell_maker(t_mini *mini, t_cell *cell, char *raw_line);
//? miniformat quotes utils
bool	is_quoted(char *str, ssize_t index);
char	*preserve_space_in_quote(t_mini *mini, char *str_to_dup);
bool	unclosed_quotes(t_mini *mini, t_char **list);
void	t_char_del_quotes(t_mini *mini, t_char **list);
void	t_char_del_pos_safe(t_mini *mini, t_char **list, t_char **current);
//? miniformat quotes
void	handle_in_quotes(t_mini *mini, t_char **list);
bool	t_char_list_format_quotes(t_mini *mini, t_char **list);
//?miniformat var
bool	is_alpha(char compare);
bool	t_char_list_cat_var(t_mini *mini, t_char **list);
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
bool	t_pipe_parse_type(t_mini *mini, t_pipe *pipe);
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
char	*get_hidden_envpl_var(t_mini *mini, char *name_var);
bool	replace_envpl_var(t_mini *mini, char *var_name, char *to_replace);
bool	add_var_envpl(t_mini *mini, char *var);
void	set_envpl_var(t_mini *mini, char *varname, char *to_replace);
void	del_var_envpl(t_mini *mini, char *var_name_to_del);
bool	copy_envp_to_list(t_mini *mini);
void	variable_content_setter(t_mini *mini, t_char **dst, char *content);
char	*variable_content_getter(t_mini *mini, t_char **dst);
size_t	var_name_size(char *var);
bool	wrong_chars_str(char *str, char *wrong_chars);
char	*get_content_var(t_mini *mini, char *name_var);
//! list_gears
//?t_char_list
void	t_char_print_typequote(t_mini *mini, t_char *list);
void	t_char_identify_typequote(t_char *list);
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
void	print_error(t_mini *mini, char *input, t_error_code code);
//?parsing_debug
void	print_t_char_list(t_mini *mini, t_char *list);
void	print_double_tab(t_mini *mini, char **tab);
//?parsing_error
bool	cells_empty_char(char *raw_line, char c);
bool	invalid_redirect(t_mini *mini, t_char **list);
//?parsing_printer
void	print_t_char(t_mini *mini, t_char *c, t_color color);
void	print_t_word(t_mini *mini, t_word *word);
void	print_t_word_list(t_mini *mini, t_word *word);
void	print_t_pipe(t_mini *mini, t_pipe *pipe);
void	print_t_pipex(t_mini *mini, t_pipex *pipex, ssize_t pos);
void	print_t_pipex_list(t_mini *mini, t_pipex *pipex);
void	print_t_cell(t_mini *mini, t_cell *cell);
void	print_envpl(int fd, t_mini *mini);
//?parsing_utils
bool	strtlen(char **tab, ssize_t *ret);
void	free_tab(char **tab);
//! string_gears
//?string_gears
char	*t_char_list_to_str(t_mini *mini, t_char *list);
char	*t_word_to_str(t_mini *mini, t_word *word);
char	*t_word_list_to_str(t_mini *mini, t_word *word);

void	handle_error(t_mini *mini, char *input, t_error_code code);

//! parsing
bool	mini_parsing(t_mini *mini, char *line);
bool	is_raw_path(t_mini *mini, char *line);

void	putstrfd(char *str, int fd);

char	*str_format_len(t_mini *mini, char *line, size_t size);
bool	t_word_parse_built_in(t_mini *mini, t_word *word);

char	*get_str(t_mini *mini, char c);
bool	is_alpha(char compare);
void	t_char_print_typequote(t_mini *mini, t_char *list);
bool	char_add_back(t_mini *mini, t_word *word, char c);
bool	char_t_char_add_back(t_mini *mini, t_char **list, char c);
void	print_t_type(t_mini *mini, t_type type);
void	print_t_word_list_double_quotes(t_mini *mini, t_char *word);

#endif
