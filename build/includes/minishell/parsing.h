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

t_mini_param pre_parsing(t_mini *mini);
t_mini_param pre_parser(t_mini *mini, t_mini_param *param);

void handle_param(t_mini *mini, char *current_param,
				  t_mini_param *mini_param);

//! printer
void	print_mini_param(t_mini *mini, t_mini_param param);

#endif