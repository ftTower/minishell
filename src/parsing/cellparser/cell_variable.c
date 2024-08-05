/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cell_variable.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 16:59:39 by tauer             #+#    #+#             */
/*   Updated: 2024/08/05 18:46:03 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/all.h>

ssize_t	count_var(char *str)
{
	ssize_t	index;
	ssize_t	ret;

	ret = 0;
	index = -1;
	while (str[++index])
	{
		if ((str[index] == '$' && str[index + 1]))
			ret++;
	}
	if (!ret)
		return (1);
	return (ret);
}

ssize_t	len_var(char *str)
{
	ssize_t	index;
	ssize_t	ret;

	index = -1;
	ret = 0;
	while (str[++index] && (str[index] == '$'))
		ret++;
	while (str[++index] && str[index] != '$')
		ret++;
	return (ret);
}

char	*get_var(t_mini *mini, char *str, ssize_t *index)
{
	char	*ret;
	ssize_t	len;
	ssize_t	cpy_index;

	len = len_var(str + *index) + 1;
	ret = mini->malloc(mini, sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	cpy_index = 0;
	while (str[*index] && (str[*index] == '$') && cpy_index < len)
		ret[cpy_index++] = str[(*index)++];
	while (str[*index] && str[*index] != '$')
		ret[cpy_index++] = str[(*index)++];
	ret[cpy_index] = '\0';
	return (ret);
}

char	**split_var(t_mini *mini, char *str)
{
	ssize_t	index;
	ssize_t	tab_index;
	char	**ret;

	if (!str)
		return (NULL);
	else if (str[0] == '$' && !str[1])
		return (NULL);
	mini->print("split_var: [%s\\0] [len : %d]\n", str, count_var(str) + 1);
	ret = mini->malloc(mini, sizeof(char *) * (count_var(str) + 1));
	if (!ret)
		return (NULL);
	index = 0;
	tab_index = 0;
	while (str[index])
		ret[tab_index++] = get_var(mini, str, &index);
	ret[tab_index] = NULL;
	return (ret);
}

void	strmcat_var(t_mini *mini, t_word *word, char **word_splitted_var)
{
	ssize_t	index;
	char	*ret;

	index = -1;
	ret = "";
	if (!word_splitted_var)
		return (word->refined_word = "", (void)0);
	print_double_tab(mini, word_splitted_var);
	while (word_splitted_var[++index])
	{
		if (!word_splitted_var[index][0])
			continue ;
		else if (word_splitted_var[index][0] == '\\' && word_splitted_var[index
			+ 1] && word_splitted_var[index + 1][0] && word_splitted_var[index
			+ 1][0] == '$' && word_splitted_var[index + 1][1])
			mini->libft->strmcat(mini->solib, &ret, word_splitted_var[index++
				+ 1]);
		else if (word_splitted_var[index][0] != '$')
			mini->libft->strmcat(mini->solib, &ret, word_splitted_var[index]);
		else if (word_splitted_var[index][1]
			&& word_splitted_var[index][0] == '$' && get_envpl_var(mini,
				word_splitted_var[index] + 1))
			mini->libft->strmcat(mini->solib, &ret, get_envpl_var(mini,
					word_splitted_var[index] + 1));
	}
	word->refined_word = ret;
}

bool	t_pipe_variable_handler(t_mini *mini, t_pipe *pipe)
{
	t_word	*current;

	current = pipe->words;
	while (current)
	{
		strmcat_var(mini, current, split_var(mini, current->refined_word));
		current = current->next;
	}
	return (false);
}
