/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almounib <almounib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:59:30 by marvin            #+#    #+#             */
/*   Updated: 2024/05/20 17:21:51 by almounib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <minishell/types.h>

int		minishell(t_solib *solib);
void	echon(char *str, int fd);
void	pwd(t_mini *mini, int fd);
void	unset(t_mini *mini, char *var_to_unset, int fd);

#endif