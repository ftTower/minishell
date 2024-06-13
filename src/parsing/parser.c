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


//* retourn a handle param la valeur apres le egal
//? verifie "=..."

t_value	get_param_value(t_solib *solib, char *value_param)
{
	if (!value_param)
		return (solib->print("Failure when parsing minishell parameters, \
				think to check in the readme to understand how to customize me"),
				exit(EXIT_FAILURE), NO);
	else if (solib->libft->strncmp(value_param, "yes", 3))
		return (YES);
	else if (solib->libft->strncmp(value_param, "no", 2))
		return (NO);
	else if (solib->libft->strncmp(value_param, "full", 4))
		return (FULL);
}


//* rempli t_mini_param a laide de chaque argv
// --display=yes
// --output=no
// --debug=yes
//? verifie "...="
//? verifie "--"

void	handle_param(t_solib *solib, char *current_param,
		t_mini_param *mini_param)
{
	if (!current_param || current_param[0] != '-' || current_param[1] != '-')
		return (solib->print("Additional parameters must begin with -- "),
			exit(EXIT_FAILURE));
	else if (solib->libft->strncmp(current_param + 2, "display=", solib->libft->strlen("display")))
		return (mini_param->display = get_param_value(solib, current_param
				+ solib->libft->strlen("display") + 3))
	else if (solib->libft->strncmp(current_param + 2, "output=" , solib->libft->strlen("output")))
		return (mini_param->output = get_param_value(solib, current_param
				+ solib->libft->strlen("output") + 3))
	else if (solib->libft->strncmp(current_param + 2, "debug=" , solib->libft->strlen("debug")))
		return (mini_param->output = get_param_value(solib, current_param
				+ solib->libft->strlen("debug") + 3))
	else
		return (solib->print("Failure when parsing minishell parameters, \
				think to check in the readme to understand how to customize me"));
}

//* modifie le comportement de minishell en fonction darguments passer en parametres;

//! a renommer pre_parser
void	parser(t_solib *solib, t_mini_param *mini_param)
{
	long index;

	index = -1;
	solib->print("pre parser\n");
	while (++index < solib->env->argc)
		handle_param(solib, solib->env->argv[index], mini_param);

	return (0);
}
