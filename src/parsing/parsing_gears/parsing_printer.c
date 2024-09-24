/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_printer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 02:37:02 by tauer             #+#    #+#             */
/*   Updated: 2024/09/19 17:45:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/all.h>

void	print_t_char(t_mini *mini, t_char *c, t_color color)
{
	if (c->c == '|')
		mini->print(" ");
	else if (color == ORANGE)
		mini->print("%Ce67e22(%c)", c->c);
	else if (color == PURPLE)
		mini->print("%Cc238eb(%c)", c->c);
	else if (color == YELLOW)
		mini->print("%Cf1c40f(%c)", c->c);
	else if (color == GREEN)
		mini->print("%C2ecc71(%c)", c->c);
	else if (color == RED)
		mini->print("%Ccb4335(%c)", c->c);
	else if (color == BLUE)
		mini->print("%C5dade2(%c)", c->c);
	else if (color == LIGHT_BLUE)
		mini->print("%C0ff1e7(%c)", c->c);
	else
		mini->print("%Cffffff(%c)", c->c);
}

void	print_t_type(t_mini *mini ,t_type type)
{
	if (type == CMD_TYPE)
		mini->print("[CMD]");
	else if (type == BUILT_IN_TYPE)
		mini->print("[BUILT IN]");
	else if (type == PARA_TYPE)
		mini->print("[PARA]");
	else if (type == ARG_TYPE)
		mini->print("[ARG]");
	else if (type == REPLACE_IN_FD_TYPE || type == REPLACE_OUT_FD_TYPE)
		mini->print("[RE FD]");
	else if (type == CONCATE_IN_FD_TYPE || type == CONCATE_OUT_FD_TYPE)
		mini->print("[CONC FD]");
	else
		mini->print("[DEFAULT]");
}

void	print_t_word(t_mini *mini, t_word *word)
{
	t_char	*current;

	current = word->c;
	print_t_type(mini, word->type);
	while (current)
	{
		if (word->type == CMD_TYPE)
			print_t_char(mini, current, LIGHT_BLUE);
		else if (word->type == BUILT_IN_TYPE)
			print_t_char(mini, current, YELLOW);
		else if (word->type == PARA_TYPE)
			print_t_char(mini, current, PURPLE);
		else if (word->type == ARG_TYPE)
			print_t_char(mini, current, BLUE);
		else if (word->type == REPLACE_IN_FD_TYPE
			|| word->type == CONCATE_IN_FD_TYPE)
			print_t_char(mini, current, GREEN);
		else if (word->type == REPLACE_OUT_FD_TYPE
			|| word->type == CONCATE_OUT_FD_TYPE)
			print_t_char(mini, current, RED);
		else
			print_t_char(mini, current, DEFAULT);
		current = current->next;
	}
	mini->print(" ");
}

void	print_t_word_list(t_mini *mini, t_word *word)
{
	t_word	*current;

	if (!word)
		return ((void)mini->print("empty"));
	current = word;
	while (current)
	{
		print_t_word(mini, current);
		current = current->next;
	}
}



void	print_t_word_list_double_quotes(t_mini *mini, t_char *word)
{

	if (!word)
		return ((void)mini->print("empty"));
	// t_char_identify_typequote(word);
	t_char_print_typequote(mini, word);
}

void	print_t_pipe(t_mini *mini, t_pipe *pipe)
{
	t_word_parse_type(mini, pipe->words);
	mini->print("\n\t╭─%Cff0000([)%C5dade2(PIPE %C0ff1e7(%d))%Cff0000(])\n\t|",
		pipe->pos);
	mini->print("\n\t├──%Cff0000([)%Cf1c40f( WORDS TYPE  )%Cff0000(]) ");
	print_t_word_list(mini, pipe->words);
	mini->print("\n\t├──%Cff0000([)%Cf1c40f( WORDS QUOTE )%Cff0000(]) ");
	print_t_word_list_double_quotes(mini, pipe->raw_words);
	mini->print("\n\t╰──%Cff0000([)%Cf1c40f(    F D S    )%Cff0000(]) ");
	print_t_word_list(mini, pipe->fds);
	mini->print("\n");
}

void	print_t_pipex(t_mini *mini, t_pipex *pipex, ssize_t pos)
{
	ssize_t index;

	index = -1;
	if (!pipex || !pipex->args)
		return ;
	mini->print("[ %Cf1c40f(%d) ]  %C2ecc71(%s) ",pos, pipex->in_fd);
	while (pipex->args[++index])
		mini->print("%s | ", pipex->args[index]);
	mini->print("%Ccb4335(%s)\n", pipex->out_fd);
}

void	print_t_pipex_list(t_mini *mini, t_pipex *pipex)
{
	t_pipex	*current;
	ssize_t	index;

	index = -1;
	mini->print("\n\t╭─%Cff0000([)%Cf1c40f(%C5dade2(PIPEX LINE))%Cff0000(])\n\t|\n");
	current = pipex;
	while (current)
	{
		if (current->next)
			mini->print("\t├──");
		else
			mini->print("\t╰──");
		print_t_pipex(mini, current, ++index);
		current = current->next;
	}
}

void	print_t_cell(t_mini *mini, t_cell *cell)
{
	ssize_t	index;

	if (!cell)
		return ((void)mini->print("empty"));
	mini->print("\n\t  %Cff0000([)%Cf1c40f(CELL %Cff0000(%d))%Cff0000(])\n",
		cell->pos);
	index = -1;
	while (++index < cell->nb_pipes)
		print_t_pipe(mini, &cell->pipes[index]);
	if (cell->final_line)
		print_t_pipex_list(mini, cell->final_line);
}


void	print_envpl(int fd, t_mini *mini)
{
	t_envpl *current;
	
	soprintf_fd(fd, "\n");
	current = mini->envpl;
	while (current)
	{
		soprintf_fd(fd, "%s\n", str_format_len(mini, current->var, 15));
		current = current->next;
	}
}
