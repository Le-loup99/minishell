/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_variables.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakoto2 <arakoto2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 08:50:40 by arakoto2          #+#    #+#             */
/*   Updated: 2025/11/25 14:05:44 by arakoto2         ###   ########.fr       */
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
	// int	len;

	// len = 0;
	i = 0;
	// e*stock = malloc (len + 1);
	// while(str[len] != '\'' && str[len] != '"' && str[len] != ' ')
	// 	len++;
	while(i < len)
	{
		stock[i] = str[i];
		i++;
	}
}

char *converter(char *str, int *i)
{
	int		len;
	char	*converted;
	char	*stock;

	len = 0;
	while(str[len + (*i) + 1] && str[len + (*i) + 1] != '\'' && str[len + (*i) + 1] != '"' && str[len + 	(*i) + 1] != ' ')
		len++;
	stock = malloc(len + 1);
	to_convert(str + (*i) + 1, stock, len);
	converted = getenv(stock);
	while(str[*i] && str[*i] != ' ' && str[*i] != '\'' && str[*i] != '"')
		(*i)++;
	printf("\n%s\n", converted);
	return (converted);
}