/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: almounib <almounib@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/04/11 21:31:29 by marvin            #+#    #+#             */
/*   Updated: 2024/05/20 17:40:22 by almounib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/all.h>
#include <sotypes/soprintf.h>

void	add_t_char(t_mini *mini, t_char **line, char c, size_t pos)
{
	t_char *new;
	t_char *current;

	new = mini->malloc(mini, sizeof(t_char));
	new->c = c;
	new->pos = pos;
	new->next = NULL;
	new->quoted = false;
	new->useless = false;
	if (c != ' ')
		new->type = UNDEFINED;
	else
	{
		new->type = SPACE_CHAR;
		new->useless = true;
	}
	if (!*line)
		return (*line = new, (void)0);
	current = *line;
	while (current->next)
		current = current->next;
	return (current->next = new, (void)0);
}

void	del_t_char(t_char **line, size_t pos_to_del)
{
	t_char *current;
	size_t correction_index;

	current = *line;
	while (current)
	{
		if (current->pos == pos_to_del - 1 && current->next
			&& current->next->next)
		{
			current->next = current->next->next;
			break ;
		}
		current = current->next;
	}
	current = *line;
	correction_index = 0;
	while (current)
	{
		current->pos = correction_index++;
		current = current->next;
	}
}

void	type_t_char(t_char **line, size_t pos_to_type, t_char_type type)
{
	t_char *current;

	current = *line;
	while (current)
	{
		if (current->pos == pos_to_type)
			current->type = type;
		current = current->next;
	}
}

t_char	*make_t_char_list(t_mini *mini, char *cell)
{
	t_char *line;
	size_t index;

	line = NULL;
	index = 0;
	while (cell[index])
	{
		add_t_char(mini, &line, cell[index], index);
		index++;
	}
	return (line);
}

void	print_t_char(t_mini *mini, bool condition, char *str)
{
	if (condition)
		mini->print("%Cff0000(%s)", str);
	else
		mini->print("%C00ff6c(%s)", str);
}

void	print_t_char_line(t_mini *mini, t_char *line)
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

void	print_cell_line(t_mini *mini, t_cell *cell, size_t index)
{
	mini->print("| %d : ", cell->mini_cells[index].pos);
	print_t_char_line(mini, cell->mini_cells[index].line);
}

void	cell_printer(t_mini *mini, t_cell *cell, bool finished_cell)
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

void	cell_init(t_mini *mini, t_cell **cell, char **raw_mini_cells,
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
	(*cell)->mini_cells = mini->malloc(mini, sizeof(t_mini_cell)
			* nb_mini_cells);
	nb_mini_cells = 0;
	while (raw_mini_cells[nb_mini_cells])
	{
		(*cell)->mini_cells[nb_mini_cells].pos = nb_mini_cells;
		(*cell)->mini_cells[nb_mini_cells].line = make_t_char_list(mini,
				raw_mini_cells[nb_mini_cells]);
		nb_mini_cells++;
	}
}

void	cell_handler(t_mini *mini, char **raw_mini_cells, size_t cell_pos)
{
	t_cell *cell;

	cell = NULL;
	//init
    cell_init(mini, &cell, raw_mini_cells, cell_pos);
	
    cell_printer(mini, cell, false);

    // travaille les chaines / verifie erreur
	
    // del_t_char( &cell->mini_cells->line, 2);
	// type_t_char(&cell->mini_cells->line, 1, CMD);

	cell_printer(mini, cell, true);
}

void	line_handler(char *line) // pas touche a ca ! okok... ;(
{
	if (line)
	{
		add_history(line);
		free(line);
	}
	rl_set_prompt("");
}

void	mini_line_handler(t_mini *mini, char *line)
{
	char **cells;
	long index;

	if (line)
	{
		// printf("You changed this into: '%s'\n", line);
		mini->print("\n");
		cells = mini->libft->split(mini->solib, line, ';');
		index = -1;
		while (cells[++index])
			cell_handler(mini, mini->libft->split(mini->solib, cells[index],
					'|'), index);
		mini->print("\n");
	}
	soprintf(" >> mini");
}

int	char_update(t_mini *mini, char **words, char *line, char c)
{
	(void)mini;
	(void)words;
	(void)line;
	(void)c;
	// mini->print("words %S\n -- %s\n ---- %c\n", words, line, c);
	return (0);
}

int	mini_start(t_mini *mini)
{
	int lenght_buffer;
	int lenght_buffer2;
	char *old_buffer;

	old_buffer = NULL;
	soprintf(" >> mini");
	rl_callback_handler_install("> ", line_handler);
	while (mini->loop)
	{
		old_buffer = mini->libft->strdup(mini->solib, rl_line_buffer);
		lenght_buffer = mini->libft->strlen(rl_line_buffer);
		rl_callback_read_char();
		lenght_buffer2 = mini->libft->strlen(rl_line_buffer);
		// printf("lenght : %d -- %d\n", lenght_buffer, lenght_buffer2);
		char_update(mini, mini->libft->split(mini->solib, rl_line_buffer, ' '),
			rl_line_buffer, rl_line_buffer[lenght_buffer - 1]);
		if (!lenght_buffer2 && lenght_buffer > 0) // enter has pressed
		{
			mini_line_handler(mini, old_buffer);
			lenght_buffer = 0;
			rl_set_prompt("> ");
			rl_redisplay();
		}
		mini->free(mini, old_buffer);
	}
	return (0);
}

int	minishell(t_solib *solib)
{
	t_mini *mini;

	mini = minit(solib);
	pre_parsing(mini);

	return (mini_start(mini));
}

// Liste des commandes pour la validation et l'autocomplétion
/*const char *commands[] = {
	"ls", "cd", "echo", "exit", "mkdir", "rmdir", "touch", "rm", "clear", NULL
};

// Couleurs ANSI pour le prompt
#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_RESET "\033[0m"














// Fonction de validation des commandes
int	is_valid_command(const char *cmd) {
	for (const char **p = commands; *p; ++p) {
		if (strcmp(*p, cmd) == 0) {
			return (1);
		}
	}
	return (0);
}

// Fonction de callback pour traiter chaque ligne saisie
void	line_handler(char *line) {
	if (line) {
		rl_insert_text("BG du 86 :");
		printf("You changed this into: '%s'\n", line);
		add_history(line);
		free(line); // Libérer la mémoire allouée par readline
		printf("MINISHELL TES MORT :");
	}
}

// Fonction de complétion
char	*command_generator(const char *text, int state) {
	static int list_index, len;
	const char *name;

	if (!state) {
		list_index = 0;
		len = strlen(text);
	}

	while ((name = commands[list_index++])) {
		if (strncmp(name, text, len) == 0) {
			return (strdup(name));
		}
	}

	return (NULL);
}

char	**command_completion(const char *text, int start, int end) {
	(void)start;
	(void)end;
	return (rl_completion_matches(text, command_generator));
}

// Fonction de callback pour traiter chaque caractère tapé
int	handle_char(int count, int key) {
	(void)count; // Utilisé pour un cas spécial de répétition
	rl_insert_text((char *)&key);
	return (0);
}

// Fonction principale du minishell
int	minishell(t_solib *solib) {
	t_mini *mini;

	mini = minit(solib);
	mini->print("MINISHELL\n");
	pre_parsing(mini);

	// Lier la fonction de complétion
	//rl_bind_key('\t', rl_insert);
	rl_attempted_completion_function = command_completion;

	// Lier toutes les touches imprimables à handle_char
	for (int i = 32; i < 127; ++i) {
		rl_bind_key(i, handle_char);
	}

	// Initialiser readline avec un prompt et une fonction de callback
	mini->print("minishell");
	rl_callback_handler_install(" >", line_handler);

	// Boucle de lecture des caractères
	while (1) {
		rl_callback_read_char(); // Lit et traite un caractère de stdin
	}
	return (0);
}*/

/*
void	line_handler(char *line) {
	if (line) {
		printf("You changed this into: '%s'\n", line);
		add_history(line);
		free(line); // Libérer la mémoire allouée par readline
	}
}

// Fonction de callback pour traiter chaque caractère tapé
int	handle_char(int count, int key) {
	(void)count; // Utilisé pour un cas spécial de répétition

	if (key == '\n') {
		// Appel de la fonction de callback readline pour gérer la ligne
		rl_callback_handler_remove();
		rl_callback_handler_install("\nminishell >", &line_handler);
		return (0);
	}

	printf("Buffer so far: %c -- '%s'\n", key, rl_line_buffer);
	return (0);
}

// Fonction principale du minishell
int	minishell(t_solib *solib) {
	t_mini *mini;

	mini = minit(solib);
	mini->print("MINISHELL\n");
	pre_parsing(mini);
	rl_bind_key('\t', rl_insert); // Utilisation de la touche Tab pour insérer
	rl_callback_handler_install("\nminishell >", &line_handler);

	// Lier toutes les touches imprimables à handle_char
	for (int i = 32; i < 127; ++i) {
		rl_bind_key(i, handle_char);
	}

	// Lier la touche Entrée à handle_char
	rl_bind_key('\n', handle_char);

	while (1) {
		rl_callback_read_char(); // Lit et traite un caractère de stdin
	}
	return (0);
}
*/