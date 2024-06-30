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

void	cell_handler(t_mini *mini, char **raw_mini_cells, size_t cell_pos);
void	cell_init(t_mini *mini, t_cell **cell, char **raw_mini_cells,
			   size_t cell_pos);
void	cell_printer(t_mini *mini, t_cell *cell, bool finished_cell);
void	print_cell_line(t_mini *mini, t_cell *cell, size_t index);
void	print_t_char_line(t_mini *mini, t_char *line);

void	print_t_char(t_mini *mini, bool condition, char *str);
t_char	*make_t_char_list(t_mini *mini, char *cell);
void	type_t_char(t_char **line, size_t pos_to_type, t_char_type type);
void	del_t_char(t_char **line, size_t pos_to_del);
void	add_t_char(t_mini *mini, t_char **line, char c, size_t pos);
#endif
