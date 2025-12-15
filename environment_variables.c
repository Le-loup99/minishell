/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_variables.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakoto2 <arakoto2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 08:50:40 by arakoto2          #+#    #+#             */
/*   Updated: 2025/12/15 11:42:25 by arakoto2         ###   ########.fr       */
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
	while(i < len && str[i] && (str[i] != '$' || (i > 0 && str[i - 1] == '$')))
	{
		stock[i] = str[i];
		i++;
	}
	stock[i] = '\0';
}

// char	*ft_get_env(char *stock_env, char *str, int i)
// {
// 	int	len;
// 	char *stock;

// 	len = 0;
// 	while(str[len + i + 1] && str[len + i + 1] != '\'' 
// 				&& str[len + i + 1] != '"' && str[len + i + 1] != ' ' && (str[len + i] != '$' || str[len + i - 1] == '$'))
// 				len++;
// 	stock = malloc(len + 1);
// 	to_convert(str + (*i) + 1 + j, stock, len);
// 	printf("\n ito le sotck %s\n", stock);
// 	// if (stock[0] == '$')
// 	// 	stock_env = getenv("SYSTEMD_EXEC_PID");
// 	stock_env = getenv(stock);
// 	if (stock)
// 		free(stock);
// 	return (stock_env);
// }

char *converter(char *str, int *i)
{
	int		len;
	char	*converted;
	char	*stock;
	char	*stock_env;
	int		j;
	int		check;

	j = 0;
	len = 0;
	check = 0;
	converted = NULL;
	stock_env = NULL;
	while (ft_strchr(str + (*i) + len, '$'))
	{
		len++;
		if (*(str + (*i) + len) == '$')
		{
			stock_env = getenv("SYSTEMD_EXEC_PID");
			len++;
			converted = ft_strjoin(converted, stock_env);
			if (*(str + (*i) + len) != '$')
			{
				while (*(str + (*i) + len) != '$' && *(str + (*i) + len) != '\'' 
					&& *(str + (*i) + len) != '"' && *(str + (*i) + len) != '\0')
				{
					converted = ft_str_p_char(converted, *(str + (*i) + len));
				 	len++;
				}
			}
		}
		else
		{
			while(str[len + (*i) + 1] && str[len + (*i) + 1] != '\'' 
				&& str[len + (*i) + 1] != '"' && str[len + (*i) + 1] != ' ' && (str[len + (*i)] != '$' || str[len + (*i) - 1] == '$'))
				len++;
			stock = malloc(len + 1);
			to_convert((str + (*i) + 1 + j), stock, len);
			printf("\n ito le sotck %s\n", stock);
			// if (stock[0] == '$')
			// 	stock_env = getenv("SYSTEMD_EXEC_PID");
			stock_env = getenv(stock);
			if (stock)
			free(stock);
			converted = ft_strjoin(converted, stock_env);
		}
		j++;
		while ((str[(*i) + j] != '$' || ((str[(*i) + j - 1] == '$') && check < 1)) && ft_strchr(str + (*i) + j, '$'))
		{
			if (str[(*i) + j] == '$')
				check = 1;
			j++;
		}
		check = 0;
	}
	// while(*(str + (*i) + len))
	// {
	// 	ft_str_p_char(converted, *(str + (*i) + len));
	// 	len++;
	// }
	while(str[*i] && str[*i] != ' ' && str[*i] != '\'' 
		&& str[*i] != '"')
		(*i)++;
	printf("\n%s\n", converted);
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
