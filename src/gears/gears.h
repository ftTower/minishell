/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 20:22:15 by marvin            #+#    #+#             */
/*   Updated: 2024/04/07 20:22:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEARS_H
# define GEARS_H

# include <minishell/all.h>

t_mini			*minit(t_solib *solib);
int				mini_close_update(t_mini *mini, int state);
int				mini_close(t_mini *mini, int state);
void			*mini_malloc(t_mini *mini, size_t size);
int				mini_free(t_mini *mini, void *ptr);
char			*display_prompt(t_mini *mini);
int				check_echo_option(char *s, char c);
char			*skipc(char **s, char c);
char			*add_c_end(t_solib *solib, char **str, char c);
int				get_c(char *str, char c);
char			*changec(char *s, char c, char to);

#endif
