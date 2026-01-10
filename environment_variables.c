/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_variables.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakoto2 <arakoto2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 08:50:40 by arakoto2          #+#    #+#             */
/*   Updated: 2026/01/09 21:30:56 by arakoto2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	ft_strcmp(const char *s1, const char *s2)
// {
// 	size_t	i;

// 	i = 0;
// 	while (s1[i] != '\0' || s2[i] != '\0')
// 	{
// 		if ((unsigned char)s1[i] != (unsigned char)s2[i])
// 			return (-3);
// 		i++;
// 	}
// 	return (0);
// }

void	to_convert(char *str, char *stock, int len)
{
	int	i;
	i = 0;
	while(i < len && str[i] && (str[i] != '$' || (i > 0 && str[i - 1] == '$')) && str[i] != '"' && str[i] != '\'')
	{
		stock[i] = str[i];
		i++;
	}
	stock[i] = '\0';
}

int	check_count_pipe(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '|')
			count++;
		i++;
	}
	return (count);
}

char *modify_str(char *str, int nbr)
{
	int	check;
	int	i;
	char *new_str;
	int	j;

	check = 0;
	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	new_str = malloc(ft_strlen(str) + nbr + 1);
	while (str[i])
	{
		if (str[i] != '|')
			check = 0;
		new_str[j] = str[i];
		if (str[i] == '|' && check == 0)
		{
			j++;
			new_str[j] = '|';
			// j++;
			check++;
		}
		i++;
		j++;
	}
	new_str[j] = '\0';
	return (new_str);
}

char *converter(char *str, int *i, t_list *env)
{
	int		len;
	char	*converted;
	char	*stock;
	char	*stock_env;
	int		j;
	int		check;
	int		count;

	j = 0;
	len = 0;
	check = 0;
	converted = NULL;
	stock_env = NULL;
	count = 0;
	while (ft_strchr(str + (*i) + len, '$'))
	{
		len++;
		if (!ft_isalnum(*(str + (*i) + len)) && *(str + (*i) + len) != '_' && *(str + (*i) + len) != '?')
		{
			if (*(str + (*i) + len) != '"' && *(str + (*i) + len) != '\'')
				converted = ft_str_p_char(converted, *(str + (*i) + len - 1));
			while (*(str + (*i) + len) == '$' && (!(check % 2) || (*(str + (*i) + len + 1) && *(str + (*i) + len + 1) == '$')))
			{
				converted = ft_str_p_char(converted, '$');
				len++;
				check++;
			}
			while (*(str + (*i) + len) != '$' && *(str + (*i) + len) != '\'' 
				&& *(str + (*i) + len) != '"' && *(str + (*i) + len) != '\0')
			{
				converted = ft_str_p_char(converted, *(str + (*i) + len));
			 	len++;
			}
		}
		else
		{
			while(str[len + (*i) + 1] && str[len + (*i) + 1] != '\'' 
				&& str[len + (*i) + 1] != '"' && str[len + (*i) + 1] != ' ' && (str[len + (*i)] != '$' || str[len + (*i) - 1] == '$'))
				len++;
			stock = malloc(len + 1);
			to_convert((str + (*i) + 1 + j), stock, len);
			stock_env = ft_return_env_value(env, stock);
			if (stock)
				free(stock);
			converted = ft_strjoin(converted, stock_env);
		}
		j++;
		check = 0;
		while ((str[(*i) + j] != '$' || ((str[(*i) + j - 1] == '$') && check < 1)) && ft_strchr(str + (*i) + j, '$'))
		{
			if (str[(*i) + j] == '$')
				check = 1;
			j++;
		}
		check = 0;
		if (stock_env)
		{
			count++;
			while ((str[(*i) + count] != '$' || ((str[(*i) + count - 1] == '$') && check < 1)) && ft_strchr(str + (*i) + j, '$'))
			{
				if (str[(*i) + count] == '$')
					check = 1;
				count++;
			}
		}
	}
	*i = *i + count;
	while(str[*i] && str[*i] != ' ' && str[*i] != '\'' 
		&& str[*i] != '"')
		(*i)++;
	check = check_count_pipe(converted);
	if (check)
		converted = modify_str(converted, check);
	// printf("\n%s\n", converted);
	return (converted);
}

int	calcul_env_size(char *str)
{
	int		i;
	int		j;
	int		len;
	char	*stock;

	i = 0;
	len = 0;
	j = 0;
	while(str[i] != '$')
		i++;
	i++;
	while(str[len + (i)] && str[len + (i)] != '\'' && str[len + i] != '"' 
		&& str[len + i + 1] != ' ')
		len++;
	while(str[len + j])
		j++;
	stock = malloc(len + 1);
	to_convert(str + i, stock, len);
	len = ft_strlen(getenv(stock));
	free(stock);
	return (len + i + j);
}
