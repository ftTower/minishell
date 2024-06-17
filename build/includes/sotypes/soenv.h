/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   soenv.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 01:57:56 by marvin            #+#    #+#             */
/*   Updated: 2024/04/30 18:09:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOENV_H
# define SOENV_H

# include <sotypes/all.h>

void	sonew_env(t_solib *solib, int argc, char **argv, char **envp);

#endif
