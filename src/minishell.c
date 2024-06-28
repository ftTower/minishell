/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almounib <almounib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 21:31:29 by marvin            #+#    #+#             */
/*   Updated: 2024/05/20 17:40:22 by almounib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/all.h>
#include <sotypes/soprintf.h>
// #include <solibft/sostring.h>

// void error_catcher()

int	is_c(char c_s, char c)
{
	return (c_s == c);
}

unsigned int	count_word(char const *s, char c)
{
	size_t			i;
	unsigned int	count;

	i = 0;
	count = 0;
	while (s[i] && s[i + 1])
	{
		if (is_c(s[i], c) && !is_c(s[i + 1], c))
			count += 1;
		else if (i == 0 && !is_c(s[i], c))
			count += 1;
		i++;
	}
	return (count);
}

char	*mal_str(char const *s, char c, int *ptr)
{
	size_t	len;
	char	*dup;

	len = 0;
	while (is_c(s[*ptr], c) && s[*ptr])
		(*ptr)++;
	while (!is_c(s[*ptr], c) && s[*ptr])
	{
		(*ptr)++;
		len++;
	}
	dup = (char *)malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	(*ptr) -= len;
	len = 0;
	while (!is_c(s[*ptr], c) && s[*ptr])
	{
		dup[len] = s[*ptr];
		(*ptr)++;
		len++;
	}
	dup[len] = '\0';
	return (dup);
}

char	**tab_tab_split(const char *s, char c)
{
	char	**tab;
	int		i;
	int		pos;
	int		count;

	i = 0;
	pos = 0;
	count = count_word(s, c);
	tab = (char **)malloc(sizeof(char *) * (count + 1));
	if (!tab)
		return (NULL);
	while (i < count)
	{
		pos = 0;
		tab[i] = mal_str(s, c, &pos);
		s += pos;
		i++;
	}
	tab[i] = 0;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab_split;

	if (!s)
		return (NULL);
	tab_split = tab_tab_split(s, c);
	return (tab_split);
}

void print_double_tab(char **tab)
{
    size_t index;

    index = 0;
    while(tab[index])
        printf("%s\n", tab[index++]);
    printf("\n\n");
}

void parsing_handler(char **cell)
{
    if (!cell)
        return ; //! exit a gerer
    print_double_tab(cell);
}

void line_handler(char *line) {
    char **cells;
    long index;
    if (line) {
        printf("You changed this into: '%s'\n", line);
        cells = ft_split(line, ';');
        if (!cells)
            return ; //! exit a gerer
        index = -1;
        while(cells[++index])
            parsing_handler(ft_split(cells[index], '|'));
        add_history(line);
        free(line); // Libérer la mémoire allouée par readline
    }
	soprintf("mini");
}

int	update(t_mini *mini, char *buffer)
{
	if (!mini->libft->strncmp(buffer, "exit", 4))
		return (mini->close(mini, EXIT_SUCCESS));
	if (!mini->libft->strncmp(buffer, "error", 5))
		return (mini->close(mini, EXIT_FAILURE));
	return (0);
}

int	mini_update(t_mini *mini)
{
	//start
	//loop a chaque char d'ecrit renvoie dans update le line buffer et le caractere ecrit
	mini->print("loop : %d\n", mini->loop);
	mini->print("minishell");
	rl_callback_handler_install(" >", line_handler);
	while (mini->loop)
	{
		rl_callback_read_char();
		if (update(mini, rl_line_buffer))
			return (1);
	}
	//minishell exit faire une fonction ou autre 
	return (0);
}

int minishell(t_solib *solib) {
    t_mini *mini;

    mini = minit(solib);
    pre_parsing(mini);

    // Lier la fonction de complétion
	//rl_bind_key('\t', rl_insert);
    //rl_attempted_completion_function = command_completion;

    // Lier toutes les touches imprimables à handle_char
    /*for (int i = 32; i < 127; ++i) {
        rl_bind_key(i, handle_char);
    }*/

    // Initialiser readline avec un prompt et une fonction de callback
    //rl_callback_handler_install(" >", line_handler);

    // Boucle de lecture des caractères
    /*while (1) {
        rl_callback_read_char(); // Lit et traite un caractère de stdin
    }*/
    return (mini_update(mini));
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
int is_valid_command(const char *cmd) {
    for (const char **p = commands; *p; ++p) {
        if (strcmp(*p, cmd) == 0) {
            return 1;
        }
    }
    return 0;
}

// Fonction de callback pour traiter chaque ligne saisie
void line_handler(char *line) {
    if (line) {
		rl_insert_text("BG du 86 :");
        printf("You changed this into: '%s'\n", line);
        add_history(line);
        free(line); // Libérer la mémoire allouée par readline
		printf("MINISHELL TES MORT :");
    }
}

// Fonction de complétion
char *command_generator(const char *text, int state) {
    static int list_index, len;
    const char *name;

    if (!state) {
        list_index = 0;
        len = strlen(text);
    }

    while ((name = commands[list_index++])) {
        if (strncmp(name, text, len) == 0) {
            return strdup(name);
        }
    }

    return NULL;
}

char **command_completion(const char *text, int start, int end) {
    (void)start;
    (void)end;
    return rl_completion_matches(text, command_generator);
}

// Fonction de callback pour traiter chaque caractère tapé
int handle_char(int count, int key) {
    (void)count; // Utilisé pour un cas spécial de répétition
    rl_insert_text((char *)&key);
    return 0;
}

// Fonction principale du minishell
int minishell(t_solib *solib) {
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
void line_handler(char *line) {
    if (line) {
        printf("You changed this into: '%s'\n", line);
        add_history(line);
        free(line); // Libérer la mémoire allouée par readline
    }
}

// Fonction de callback pour traiter chaque caractère tapé
int handle_char(int count, int key) {
    (void)count; // Utilisé pour un cas spécial de répétition

    if (key == '\n') {
        // Appel de la fonction de callback readline pour gérer la ligne
        rl_callback_handler_remove();
        rl_callback_handler_install("\nminishell >", &line_handler);
        return 0;
    }

    printf("Buffer so far: %c -- '%s'\n", key, rl_line_buffer);
    return 0;
}

// Fonction principale du minishell
int minishell(t_solib *solib) {
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