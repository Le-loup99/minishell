#include "minishell.h"

char	*filename_handler(char *str, char *cleared)
{
	int i;
	int	j;
	int quote;

	i = 0;
	j = 0;
	quote = 0;
	while (str && str[i])
	{
		cleared[j] = '\0';
		if(str[i] == '\'' && quote == 0)
		{
			quote = 1;
			i++;
		}
		else if (str[i] == '"' && quote == 0)
		{
			quote = 2;
			i++;
		}
		if (str[i] == '\'' && quote == 1)
		{
			quote = 0;
			i++;
		}
		else if (str[i] == '"' && quote == 2)
		{
			quote = 0;
			i++;
		}
		if ((str[i] == '\'' && quote == 2) || (str[i] == '"' && quote == 1) || (str[i] != '\'' && str[i] != '"'))
		{
			cleared = ft_str_p_char(cleared, str[i]);
				j++;
			if (str[i])
				i++;
		}
	}
	return (cleared);
}

char	*line_handler(char **str, char *cleared, t_list *env)
{
	int		i;
	int		j;
	char	*tmp;

	j = 0;
	i = 0;
	if (!str)
		return (NULL);
	// if (!quote_checker(*str))
	// {
	// 	while (*str && (*str)[i])
	// 	{
	// 		if((*str)[i] == '\'' && quote == 0)
	// 		{
	// 			quote = 1;
	// 			i++;
	// 		}
	// 		else if ((*str)[i] == '"' && quote == 0)
	// 		{
	// 			quote = 2;
	// 			i++;
	// 		}
	// 		if ((*str)[i] == '\'' && quote == 1)
	// 		{
	// 			quote = 0;
	// 			i++;
	// 		}
	// 		else if ((*str)[i] == '"' && quote == 2)
	// 		{
	// 			quote = 0;
	// 			i++;
	// 		}
	// 		if ((*str)[i] == '$' && quote != 1)
	// 		{
	// 			cleared[j] = '\0';
	// 			tmp = converter(*str, &i);
	// 			if (tmp)
	// 				cleared = ft_strjoin_pars(cleared, tmp);
	// 			while (cleared[j])
	// 				j++;
	// 			if (tmp)
	// 				free(tmp);
	// 		}
	// 		if (((*str)[i] == '\'' && quote == 2) || ((*str)[i] == '"' && quote == 1) || ((*str)[i] != '\'' && (*str)[i] != '"'))
	// 		{
	// 			cleared = ft_str_p_char(cleared, (*str)[i]);
	// 			j++;
	// 			if ((*str)[i])
	// 				i++;
	// 		}
	// 	}
	// 	if (cleared[j - 1])
	// 		cleared[j] = '\0';
	// }
	// else if(quote_checker(str) == 2)
	while ((*str)[i])
	{
        if ((*str)[i] == '$')
		{
			cleared[j] = '\0';
			tmp = converter(*str, &i, env);
			if (tmp)
				cleared = ft_strjoin_pars(cleared, tmp);
			while (cleared[j])
				j++;
			if (tmp)
				free(tmp);
		}
		cleared = ft_str_p_char(cleared, (*str)[i]);
		j++;
		if ((*str)[i])
			i++;
	}
	cleared[j] = '\0';
	return (cleared);
}
