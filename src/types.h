/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almounib <almounib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 21:27:45 by marvin            #+#    #+#             */
/*   Updated: 2024/05/16 15:11:46 by almounib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
#include <readline/rltypedefs.h>
# include <stdbool.h>
# include <sotypes.h>
# include <solibft.h>

typedef struct s_mini		t_mini;
typedef struct s_mini_param	t_mini_param;

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
	bool	no_param;
	t_value display;
	t_value output;
	t_value debug;
} t_mini_param;

typedef enum e_char_type
{
	UNDEFINED,
	IN_FD,
	OU_FD,
	CMD,
	PARA,
}	t_char_type;

typedef struct s_char
{
	char c;
	t_char_type type;
	size_t pos;
	
	bool useless;
	bool quoted;
	
	struct s_char *next;
}	t_char;

typedef struct s_mini_cell
{
	size_t pos;

	int in_fd;
	char in_fd_path;
	
	int out_fd;
	char out_fd_path;

	t_char *work_line;
	char   *line;

}	t_mini_cell;

typedef struct s_cell
{
	size_t pos;
	char **cmd_line;
	t_mini_cell *cells;
}	t_cell;

typedef struct s_mini
{
	int			loop;
	int			starting;
	t_solib		*solib;
	t_solibft	*libft;
	t_soenv		*env;
	int			(*print)(const char *str, ...);
	void		*(*malloc)(t_mini *mini, size_t size);
	int			(*free)(t_mini *mini, void *ptr);
	int			(*close)(t_mini *mini, int state);
} t_mini;

#endif

