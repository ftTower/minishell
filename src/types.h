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

# include <stdio.h>
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

typedef enum e_color
{
    ORANGE,
    PURPLE,
    YELLOW,
    GREEN,
	BLUE,
    RED,
	DEFAULT,
} t_color;

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
	CMD_TYPE,
	ARG_TYPE,
	PARA_TYPE,


	REPLACE_IN_FD_TYPE,
	REPLACE_OUT_FD_TYPE,
	CONCATE_OUT_FD_TYPE,
	CONCATE_IN_FD_TYPE,

	ERROR_TYPE,

	BUILT_IN_TYPE,
	BUILT_IN_PARA_TYPE,
} t_type;

typedef struct s_char
{
	char c;
	size_t pos;
	struct s_char *next;
} t_char;

typedef struct s_word
{
	t_char *c;
	t_type type;
	ssize_t pos;

	char *refined_word;
	struct s_word *next;
} t_word;

typedef struct s_pipe
{
	t_char *raw_words;

	t_word *in_fd;
	t_word *words;
	t_word *ou_fd;

	ssize_t pos;
} t_pipe;

//  ; ls | cat -e | cat ;
typedef struct s_cell
{
	char **lines;

	ssize_t nb_pipes;
	ssize_t pos;

	t_pipe *pipes;

} t_cell;

typedef struct s_envpl
{
	char *var;
	struct s_envpl *next;
}	t_envpl;

typedef struct s_mini
{
	int loop;
	int starting;
	t_solib *solib;
	t_solibft *libft;
	t_soenv *env;
	t_envpl *envpl;
	int (*print)(const char *str, ...);
	void *(*malloc)(t_mini *mini, size_t size);
	int (*free)(t_mini *mini, void *ptr);
	int (*close)(t_mini *mini, int state);
} t_mini;

#endif
