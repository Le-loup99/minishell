/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_variables.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakoto2 <arakoto2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 08:50:40 by arakoto2          #+#    #+#             */
/*   Updated: 2025/12/02 17:10:39 by arakoto2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return (-3);
		i++;
	}
	return (0);
}

void	to_convert(char *str, char *stock, int len)
{
	int	i;
	i = 0;
	while(i < len && str[i] != '$')
	{
		stock[i] = str[i];
		i++;
	}
	stock[i] = '\0';
}

char *converter(char *str, int *i)
{
	int		len;
	char	*converted;
	char	*stock;
	char	*stock_env;

	len = 0;
	converted = NULL;
	while (ft_strchr(str + (*i) + len, '$'))
	{
		len++;
		while(str[len + (*i) + 1] && str[len + (*i) + 1] != '\'' 
			&& str[len + (*i) + 1] != '"' && str[len + (*i) + 1] != ' ' && str[len + (*i)] != '$')
			len++;
		stock = malloc(len + 1);
		to_convert(str + (*i) + 1, stock, len);
		stock_env = getenv(stock);
		converted = ft_strjoin(converted, stock_env);
	}
	while(str[*i] && str[*i] != ' ' && str[*i] != '\'' && str[*i] != '"')
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