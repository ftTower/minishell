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

void print_t_char_line(t_mini *mini, t_char *line)
{
	t_char *current;

	current = line;
	while (current)
	{
		print_t_char(mini, current->useless, "[");
		if (current->type == UNDEFINED)
			mini->print("%Cc5bebe(%c)", current->c);
		else if (current->type == CMD)
			mini->print("%Cff0000(%c)", current->c);
		else if (current->type == SPACE_CHAR)
			mini->print(" ");

		print_t_char(mini, current->useless, "]");
		current = current->next;
	}
	mini->print("\n");
}

void print_cell_line(t_mini *mini, t_cell *cell, size_t index)
{
	mini->print("| %d : ", cell->mini_cells[index].pos);
	print_t_char_line(mini, cell->mini_cells[index].line);
}

void cell_printer(t_mini *mini, t_cell *cell, bool finished_cell)
{
	size_t index;

	index = 0;
	if (!cell)
		return (mini->print("fack no cell received\n"), (void)0);
	if (!finished_cell)
		mini->print("+=[%d]\t(%d mini cells)\n", cell->pos,
					cell->nb_mini_cells);
	while (index < cell->nb_mini_cells)
		print_cell_line(mini, cell, index++);
	mini->print("+==========================\n");
	if (finished_cell)
		mini->print("\n");
}

void cell_init(t_mini *mini, t_cell **cell, char **raw_mini_cells,
			   size_t cell_pos)
{
	size_t nb_mini_cells;

	*cell = mini->malloc(mini, sizeof(t_cell));
	nb_mini_cells = 0;
	while (raw_mini_cells[nb_mini_cells])
		nb_mini_cells++;
	(*cell)->nb_mini_cells = nb_mini_cells;
	(*cell)->pos = cell_pos;
	(*cell)->raw_mini_cells = raw_mini_cells;
	(*cell)->mini_cells = mini->malloc(mini, sizeof(t_mini_cell) * nb_mini_cells);
	nb_mini_cells = 0;
	while (raw_mini_cells[nb_mini_cells])
	{
		(*cell)->mini_cells[nb_mini_cells].pos = nb_mini_cells;
		(*cell)->mini_cells[nb_mini_cells].line = make_t_char_list(mini,
																   raw_mini_cells[nb_mini_cells]);
		nb_mini_cells++;
	}
}

void cell_handler(t_mini *mini, char **raw_mini_cells, size_t cell_pos)
{
	t_cell *cell;

	cell = NULL;
	// init
	cell_init(mini, &cell, raw_mini_cells, cell_pos);

	cell_printer(mini, cell, false);

	// travaille les chaines / verifie erreur

	// del_t_char( &cell->mini_cells->line, 2);
	// type_t_char(&cell->mini_cells->line, 1, CMD);

	cell_printer(mini, cell, true);
}