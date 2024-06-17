/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sotypes_t.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 21:27:45 by marvin            #+#    #+#             */
/*   Updated: 2024/06/05 17:46:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOTYPES_T_H
# define SOTYPES_T_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# define TRUE 1
# define FALSE 0

typedef struct s_solib			t_solib;
typedef struct s_somemory		t_somemory;
typedef struct s_somemdata		t_somemdata;
typedef struct s_sofuncs		t_sofuncs;
typedef struct s_solibft		t_solibft;
typedef struct s_so				t_so;

typedef struct s_somemdata {
	void		*ptr;
	t_somemdata	*next;
}	t_somemdata;

typedef struct s_somemory
{
	t_somemdata	*first;
	void		(*show)(t_solib *solib);
	t_somemdata	*(*remove)(t_solib *solib, void *ptr);
	void		(*clear)(t_solib *solib);
	void		(*add)(t_solib *solib, void *ptr);
	void		(*close)(t_solib *solib);
}	t_somemory;

typedef struct s_soenv
{
	char	*name;
	int		argc;
	char	**argv;
	char	**envp;
}	t_soenv;

typedef struct s_solib
{
	t_somemory	*memory;
	t_soenv		*env;
	t_sofuncs	*funcs;
	int			(*close)(t_solib *solib, int state);
	void		*(*malloc)(t_solib *solib, size_t size);
	int			(*free)(t_solib *solib, void *ptr);
	int			(*print)(const char *str, ...);
	t_solibft	*libft;
	t_so		*so;
}	t_solib;

#endif