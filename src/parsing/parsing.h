/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pswp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almounib <almounib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 01:57:56 by marvin            #+#    #+#             */
/*   Updated: 2024/05/16 15:15:57 by almounib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <minishell/all.h>

typedef enum e_value
{
	YES,
	NO,
	FULL,
}	t_value;

typedef struct s_mini_param
{
	t_value display;
	t_value output;
	t_value debug;
}	t_mini_param;


int	parsing(t_solib *solib);
int	parser(t_solib *solib);

#endif