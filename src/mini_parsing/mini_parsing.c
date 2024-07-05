/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pswp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almounib <almounib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 18:16:39 by marvin            #+#    #+#             */
/*   Updated: 2024/05/16 15:15:49 by almounib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/all.h>
#include <sotypes/soprintf.h>


// l'ideal serait que vue que mini est deja instancier pre_parsing return un int 1 error 0 good
// rajouter dans types.h et t_mini ton mini_param exemple t_mini_param *param; et l'associer directement avec pres parser
// (si j'ai bien compris ton code)

t_mini_param	pre_parsing(t_mini *mini)
{
	t_mini_param param;
	
	mini->print("%Cd6f27c( \
	Program name : %Cc238eb(%s)\n \
	Number of argument : %Cebba38(%d)\n \
	Aruments : \n%C38eb4b(%S) \
	Envp is init : %b\n)",
	mini->env->name, mini->env->argc, mini->env->argv, mini->env->envp);
	return (pre_parser(mini, &param));
}