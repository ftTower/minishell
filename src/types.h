/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: almounib <almounib@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/04/11 21:27:45 by marvin            #+#    #+#             */
/*   Updated: 2024/05/16 15:11:46 by almounib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <readline/history.h>
# include <readline/readline.h>
# include <readline/rltypedefs.h>
# include <solibft.h>
# include <sotypes.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_mini t_mini;
typedef struct s_mini_param t_mini_param;

// ls | cat -e ; cat | cat | cat ; echo "coucou"

typedef enum e_value
{
	YES,
	NO,
	FULL,
	ERROR,
	UNSET,
} t_value;

typedef struct s_mini_param
{
	bool no_param;
	t_value display;
	t_value output;
	t_value debug;
} t_mini_param;

typedef enum e_type
{
	CMD,
	ARG,
	PARA,
	IN_FD,
	OU_FD,

	BUILT_IN,
	BUILT_IN_PARA,
} t_type;

typedef struct s_char
{
	char c;
	struct s_char *next;
} t_char;

typedef struct s_word
{
	t_char *c;
	char *refined_word;
	t_type type;
	struct s_word *next;
} t_word;

typedef struct s_pipe
{
	t_word *words;
} t_pipe;

//  ; ls | cat -e | cat ;
typedef struct s_cell
{
	char **lines;

	ssize_t nb_pipes;
	size_t pos;

	t_pipe *pipes;

} t_cell;

typedef struct s_mini
{
	int loop;
	int starting;
	t_solib *solib;
	t_solibft *libft;
	t_soenv *env;
	int (*print)(const char *str, ...);
	void *(*malloc)(t_mini *mini, size_t size);
	int (*free)(t_mini *mini, void *ptr);
	int (*close)(t_mini *mini, int state);
} t_mini;

#endif
