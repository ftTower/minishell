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
# include <stdio.h>
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
} t_value;

typedef struct s_mini_param
{
	bool	no_param;
	t_value display;
	t_value output;
	t_value debug;
} t_mini_param;

typedef struct s_mini
{
	int			loop;
	t_solib		*solib;
	t_solibft	*libft;
	t_soenv		*env;
	int			(*print)(const char *str, ...);
	void		*(*malloc)(t_mini *mini, size_t size);
	int			(*free)(t_mini *solib, void *ptr);
	int			(*close)(t_mini *mini, int state);
} t_mini;

#endif

