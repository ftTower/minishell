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
#include <readline/readline.h>
#include <readline/history.h>
#include <readline/rltypedefs.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Liste des commandes pour la validation et l'autocomplétion
const char *commands[] = {
    "ls", "cd", "echo", "exit", "mkdir", "rmdir", "touch", "rm", NULL
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
        printf("You changed this into: '%s'\n", line);
        add_history(line);
        free(line); // Libérer la mémoire allouée par readline
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

// Variable pour stocker la couleur actuelle du prompt
char *current_color = COLOR_RESET;

// Fonction de mise à jour du prompt en fonction de la validité de la commande
void update_prompt() {
    char *line = rl_line_buffer;
    if (is_valid_command(line)) {
        if (strcmp(current_color, COLOR_RED) != 0) {
            rl_replace_line(line, 0);
            rl_redisplay();
            printf("%s", COLOR_GREEN);
            current_color = COLOR_GREEN;
        }
    } else {
        if (strcmp(current_color, COLOR_GREEN) != 0) {
            rl_replace_line(line, 0);
            rl_redisplay();
            printf("%s", COLOR_RED);
            current_color = COLOR_RED;
        }
    }
}

// Fonction de callback pour traiter chaque caractère tapé
int handle_char(int count, int key) {
    (void)count; // Utilisé pour un cas spécial de répétition
    rl_insert_text((char *)&key);
    update_prompt();
    return 0;
}

// Fonction principale du minishell
int minishell(t_solib *solib) {
    t_mini *mini;

    mini = minit(solib);
    mini->print("MINISHELL\n");
    pre_parsing(mini);

    // Lier la fonction de complétion
    rl_attempted_completion_function = command_completion;

    // Lier toutes les touches imprimables à handle_char
    for (int i = 32; i < 127; ++i) {
        rl_bind_key(i, handle_char);
    }

    // Initialiser readline avec un prompt et une fonction de callback
    rl_callback_handler_install("minishell > ", line_handler);

    // Boucle de lecture des caractères
    while (1) {
        rl_callback_read_char(); // Lit et traite un caractère de stdin
    }
    return (0);
}

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