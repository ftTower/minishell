
#include <minishell/all.h>

bool	is_quoted(char *str, ssize_t index)
{
	ssize_t start;

	start = index;
	while (start > 0 && str[start] != '"')
		--start;
	while (str[++index])
		if (str[start] == '"' && str[index] == '"')
			return (true);
	return (false);
}

char	*preserve_space_in_quote(t_mini *mini, char *str_to_dup)
{
	ssize_t index;
	char *dup;
	bool	double_quotes;

	double_quotes = false;
	index = -1;
	dup = mini->malloc(mini, sizeof(char) * (mini->libft->strlen(str_to_dup)
				+ 1));
	while (str_to_dup[++index])
	{
		if (str_to_dup[index] == '"')
		{
			if (!double_quotes)
				double_quotes = true;
			else
				double_quotes = false;
		}
		if (str_to_dup[index] == ' ' && double_quotes)
			dup[index] = '|';
		else
			dup[index] = str_to_dup[index];
	}
	return (dup[index] = '\0', dup);
}
