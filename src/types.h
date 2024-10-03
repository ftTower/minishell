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

# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <readline/rltypedefs.h>
# include <solibft.h>
# include <sotypes.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
#include <dirent.h>
# include <unistd.h>

typedef struct s_mini t_mini;
typedef struct s_mini_param t_mini_param;

extern volatile sig_atomic_t	g_signal;

// echo start | cat -e >test  | ls -la | cat -e

typedef enum e_color
{
	ORANGE,
	PURPLE,
	YELLOW,
	GREEN,
	BLUE,
	LIGHT_BLUE,
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

	BUILT_IN_TYPE,
	BUILT_IN_PARA_TYPE,

	SEPARATOR_TYPE,
	ERROR_TYPE,
} t_type;

typedef enum s_type_quotes
{
	TYPEQUOTES_UNSET,
	TYPEQUOTES_UNQUOTED,
	TYPEQUOTES_SINGLE_QUOTED,
	TYPEQUOTES_DOUBLE_QUOTED,
	TYPEQUOTES_BOTH_QUOTED,
	TYPEQUOTES_TO_KEEP,
	TYPEQUOTES_PATH,
} t_type_quotes;

typedef enum s_error_code
{
	ERROR_UNSET,
	ERROR_EMPTY_SEMICOLON,
	ERROR_EMPTY_PIPE,
	ERROR_EMPTY_REDIRECT,
	ERROR_INVALID_REDIRECT,
	ERROR_TOO_MANY_REDIRECT,
	ERROR_FAILED_OPEN_IN_FD,
	ERROR_FAILED_OPEN_OUT_FD,
	ERROR_TYPE_NO_CMD,
} t_error_code;

typedef struct s_char
{
	char c;
	size_t pos;
	t_type_quotes type_quotes;
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

	t_word *fds;
	t_word *words;

	ssize_t pos;
	bool used;
} t_pipe;

typedef struct s_pipex
{
	char *in_fd;
	char **args;
	char *out_fd;

	struct s_pipex *next;
} t_pipex;

//  ; ls | cat -e | cat ;

typedef struct s_cell
{
	t_pipe *pipes;
	ssize_t nb_pipes;
	ssize_t pos;

	t_pipex *final_line;
} t_cell;

typedef struct s_envpl
{
	char *var;
	struct s_envpl *next;
} t_envpl;

typedef struct s_history
{
	char *line;
	ssize_t pos;
	bool	success;
	t_cell *cell;
	struct s_history *next;
}	t_history;

typedef struct s_mini
{
	int loop;
	int starting;
	t_solib *solib;
	t_solibft *libft;
	t_soenv *env;
	t_envpl *envpl;
	t_history *history;
	int history_pos;
	int (*print)(const char *str, ...);
	void *(*malloc)(t_mini *mini, size_t size);
	int (*free)(t_mini *mini, void *ptr);
	int (*close)(t_mini *mini, int state);
} t_mini;

#endif
