/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cell_variable.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 16:59:39 by tauer             #+#    #+#             */
/*   Updated: 2024/08/03 01:47:16 by tauer            ###   ########.fr       */
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
		if (str[index] == '$' && str[index + 1] && str[index + 1] != ' ')
			ret++;
	return (printf("count_var : %ld\n", ret), ret);
}

ssize_t	len_var(char *str)
{
	ssize_t	index;
	ssize_t	ret;

	index = -1;
	ret = 0;
	while (str[++index])
		if (index == 0 || str[index] != '$')
			ret++;
	return (ret);
}

bool	fill_var(char *src, char *dst)
{
	ssize_t	index;

	index = -1;
	printf("[%s] - ", src);
	while (src[++index] && src[index] && (index == 0 || src[index] != '$'))
		dst[index] = src[index];
	dst[++index] = '\0';
	printf("[%s]\n", dst);
	return (false);
}

char	**split_var(char *str)
{
	ssize_t	index;
	ssize_t	tab_index;
	ssize_t	char_index;
	char	**ret;
	char	*buf;

	ret = malloc(sizeof(char *) * (count_var(str) + 1));
	if (!ret)
		return (NULL);
	index = -1;
	tab_index = 0;
	while (str[++index])
	{
		printf("%s\n", str + index);
		if (str[index] == '$')
		{
			
			printf("dollar : %ld len_var[%ld]\n", index, len_var(str + index) + 1);
			buf = malloc(sizeof(char) * (len_var(str + index) + 1));
			if (!buf)
				return (NULL);
			char_index = 0;
			while (str[index] && str[index + 1] != '$')
				buf[char_index++] = str[index++];
			buf[char_index] = '\0';
			ret[tab_index++] = buf;
			if (!str[index])
				break;
		}
	}
	ret[tab_index] = NULL;
	return (printf("================\n"), ret);
}

bool	t_pipe_variable_handler(t_mini *mini, t_pipe *pipe)
{
	t_word	*current;

	current = pipe->words;
	while (current)
	{
		print_double_tab(mini, split_var(current->refined_word));
		mini->print("\n");
		current = current->next;
	}
	return (false);
}
