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
#define PARSING_H

#include <minishell/all.h>
#include <stdbool.h>

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

t_mini_param pre_parsing(t_solib *solib);
t_mini_param pre_parser(t_solib *solib, t_mini_param *param);

void handle_param(t_solib *solib, char *current_param,
				  t_mini_param *mini_param);

//! printer
void	print_mini_param(t_solib *solib, t_mini_param param);

#endif