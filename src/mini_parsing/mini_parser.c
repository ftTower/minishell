/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pswp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: almounib <almounib@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/02/27 18:16:39 by marvin            #+#    #+#             */
/*   Updated: 2024/05/16 15:15:49 by almounib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/all.h>
#include <sotypes/soprintf.h>

void	print_t_value(t_mini *mini, t_value value, char *name)
{
	mini->print("\t%Cd6f27c(%s)%Cd6f27c( -> )", name);
	if (value == ERROR)
		mini->print("%Cff0000(ERROR)\n");
	else if (value == FULL)
		mini->print("%Cff0000(FULL)\n");
	else if (value == YES)
		mini->print("%Cff0000(YES)\n");
	else if (value == NO)
		mini->print("%Cff0000(NO)\n");
	else
		mini->print("%Cff0000(UNSET)\n");
}

void	print_mini_param(t_mini *mini, t_mini_param param)
{
	mini->print("\n");
	print_t_value(mini, param.display, "display");
	print_t_value(mini, param.output, "output");
	print_t_value(mini, param.debug, "debug");
}

bool	find_keyword(t_mini *mini ,char *find_in, char *to_find)
{
	long index;

	if (!find_in || !to_find)
		return (false);
	index = -1;
	while(find_in[++index])
		if (!mini->libft->strncmp(find_in + index, to_find, mini->libft->strlen(to_find)))
			return (true);
	return (false);
}


// bool	find_keyword_list(t_mini *mini, char *find_in, char *to_find)
// {
// 	if (open())
// }


//! logique simple cherche dans largv a trouver des mots cles

// * a terme cherchera en second lieu les valeurs (yes/no/full/...)

// * a terme find_keyword_list ira open un fichier contenant des possibilites
// * de keyword (similaire/diminue)

void	handle_param(t_mini *mini, t_mini_param *mini_param, char *current_param, long index)
{
	mini->print("[%d][%Cff004d(%s)] : %Cff0000(found) ", index, current_param);
	if (find_keyword(mini, current_param, "display"))
		mini->print("display\n");
	else if (find_keyword(mini, current_param, "output"))
		mini->print("output\n");
	else if (find_keyword(mini, current_param, "debug"))
		mini->print("debug\n");
	else
		mini->print(" nothing cool\n");
	mini_param->no_param = false;
}

//* modifie le comportement de minishell en fonction darguments passer en parametres;

t_mini_param pre_parser(t_mini *mini, t_mini_param *mini_param)
{
	long index;

	index = -1;
	mini->print("==========pre parser==============\n");
	mini_param->no_param = true;
	mini_param->display = UNSET;
	mini_param->output = UNSET;
	mini_param->debug = UNSET;
	if (mini->env->argc)
	{
		while (++index < mini->env->argc)
			handle_param(mini, mini_param, mini->env->argv[index], index);
		print_mini_param(mini, *mini_param);
	}
	else
	{
		mini->print("No configuration detected, running basic version of Minishell\n");
	}
	return (mini->print("===============================\n\n"), *mini_param);
}
