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
	print_t_value(mini, param.display, "display");
	print_t_value(mini, param.output, "output");
	print_t_value(mini, param.debug, "debug");
}


//* retourn a handle param la valeur apres le egal
//? verifie "=..."

t_value get_param_value(t_mini *mini, char *value_param, char *err_msg)
{
	mini->print("reading value of [%s] param\n", value_param);
	if (!value_param)
		return (mini->print("%s", err_msg), exit(EXIT_FAILURE), ERROR);
	else if (mini->libft->strncmp(value_param, "yes", 3))
		return (YES);
	else if (mini->libft->strncmp(value_param, "no", 2))
		return (NO);
	else if (mini->libft->strncmp(value_param, "full", 4))
		return (FULL);
	else
		return (mini->print("%s", err_msg), exit(EXIT_FAILURE), ERROR);
}

//* rempli t_mini_param a laide de chaque argv
// --display=yes
// --output=no
// --debug=yes
//? verifie "...="
//? verifie "--"

void handle_param(t_mini *mini, char *current_param,
				  t_mini_param *mini_param)
{
	char *err_msg;

	err_msg = "Failure when parsing minishell parameters, think to check in the readme to understand how to customize me ";
		mini->print("[%s] - ",current_param);
	if (!current_param || current_param[0] != '-' || current_param[1] != '-')
		return (mini->print("Additional parameters must begin with --\n"), (void)0);
	else if (mini->libft->strncmp(current_param + 2, "display=", 8))
		mini_param->display = get_param_value(mini, current_param + 10, err_msg);
	else if (mini->libft->strncmp(current_param + 2, "output=", 7))
		mini_param->output = get_param_value(mini, current_param + 9, err_msg);
	else if (mini->libft->strncmp(current_param + 2, "debug=", 7))
		mini_param->output = get_param_value(mini, current_param + 9, err_msg);
	else
	{
		mini->print("[%s] : %s\n",current_param, err_msg);
		return ;
	}
	mini_param->no_param = false;
}

//* modifie le comportement de minishell en fonction darguments passer en parametres;

t_mini_param pre_parser(t_mini *mini, t_mini_param *mini_param)
{
	long index;

	index = -1;
	mini->print("pre parser\n");
	mini_param->no_param = true;
	mini_param->display = NO;
	mini_param->output = NO;
	mini_param->debug = NO;
	if (mini->env->argc)
	{
		while (++index < mini->env->argc)
			handle_param(mini, mini->env->argv[index], mini_param);
		print_mini_param(mini, *mini_param);
	}
	else
		mini->print("No configuration detected, running basic version of Minishell");
	return (*mini_param);
}
