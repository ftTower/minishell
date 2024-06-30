/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:08:01 by marvin            #+#    #+#             */
/*   Updated: 2024/06/05 18:08:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/all.h>
#include <sotypes/soprintf.h>

void line_handler() // pas touche a ca ! okok... ;(
{
	return ;
}

void mini_prompt()
{
	rl_replace_line("", -1); // Efface la ligne courante
	soprintf(" >> mini >");
	rl_on_new_line(); // Remet le prompt sur une nouvelle ligne
	rl_redisplay();	  // Redess
}