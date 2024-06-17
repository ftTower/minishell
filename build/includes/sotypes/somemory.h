/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   somemory.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 01:57:56 by marvin            #+#    #+#             */
/*   Updated: 2024/05/04 17:03:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOMEMORY_H
# define SOMEMORY_H

# include <sotypes/all.h>

int				sonew_memory(t_solib *solib);
void			somemory_show(t_solib *solib);
t_somemdata		*somemory_remove(t_solib *solib, void *ptr);
void			somemory_clear(t_solib *solib);
void			somemory_add(t_solib *solib, void *ptr);
void			*somalloc(t_solib *solib, size_t size);
int				sofree(t_solib *solib, void *ptr);
#endif
