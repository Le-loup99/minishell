/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakoto2 <arakoto2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 12:16:29 by arakoto2          #+#    #+#             */
/*   Updated: 2025/12/15 10:44:41 by arakoto2         ###   ########.fr       */
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
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if ((!s1[i] && s2[i]) || (s1[i] && !s2[i]))
		return (20);
	return (0);
}

int	ft_strchr(const char *s, int c)
{
	int		i;
	char	*stock;

	stock = (char *) s;
	i = 0;
	while (stock[i] != '\0')
	{
		if ((unsigned char)stock[i] == (unsigned char)c)
			return (1);
		i++;
	}
	return (0);
}

int	quote_checker(char *str)
{
    int	i;

	i = 0;
	if (str[i] == '\'')
	{
		// if (ft_strchr(str, '$'))
		// 	return (1);
		if (ft_strchr(str, '*'))
			return (1);
		if (ft_strchr(str, '?'))
			return (1);
		if (ft_strchr(str, ';'))
			return (1);
		if (ft_strchr(str, '|'))
			return (1);
		if (ft_strchr(str, '&'))
			return (1);
		if (ft_strchr(str, '('))
			return (1);
		if (ft_strchr(str, ')'))
			return (1);
		if (ft_strchr(str, '{'))
			return (1);
		if (ft_strchr(str, '}'))
			return (1);
		if (ft_strchr(str, '\\'))
			return (1);
		if (ft_strchr(str, '>'))
			return (1);
		if (ft_strchr(str, '<'))
			return (1);
	}
	else if (str[i] == '"')
	{
		if (ft_strchr(str, '*'))
			return (1);
		if (ft_strchr(str, '?'))
			return (1);
		if (ft_strchr(str, ';'))
			return (1);
		if (ft_strchr(str, '|'))
			return (1);
		if (ft_strchr(str, '&'))
			return (1);
		if (ft_strchr(str, '>'))
			return (1);
		if (ft_strchr(str, '<'))
			return (1);
	}
	return (0);
}

char	*ft_str_p_char(char *s1, char a)
{
	char	*final;
	int		i;

	i = 0;
	final = malloc (ft_strlen(s1) + 2);
	while (s1 && s1[i])
	{
		final[i] = s1[i];
		i++;
	}
	final[i] = a;
	i++;
	final[i] = '\0';
	if (s1)
		free(s1);
	return (final);
}

char	*ft_strjoin(char *dst, char *src)
{
	int		dstsize;
	int		srcsize;
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	dstsize = ft_strlen(dst);
	srcsize = ft_strlen(src);
	tmp = malloc (dstsize + srcsize + 1);
	while (dst && dst[i])
	{
		tmp[i] = dst[i];
		i++;
	}
	while (src && src[j])
	{
		tmp[i + j] = src[j];
		j++;
	}
	tmp[i + j] = '\0';
	if (dst)
		free(dst);
	return (tmp);
}

void	ft_strcat(char *dst, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!src)
		return ;
	while (dst[i])
		i++;
	while (src[j])
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return ;
}

char	*quote_clearer(char *str, char *cleared)
{
	int		quote;
	int		i;
	int		j;
	char	*tmp;

	j = 0;
	i = 0;
	quote = 0;
	if (!str)
		return (NULL);
	if (!quote_checker(str))
	{
		while (str && str[i])
		{
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
			if (str[i] == '$' && quote != 1)
			{
				cleared[j] = '\0';
				tmp = converter(str, &i);
				if (tmp)
					cleared = ft_strjoin(cleared, tmp); // verifieo sao dia mi segfault
				while (cleared[j])
					j++;
				if (tmp)
					free(tmp);
			}
			if ((str[i] == '\'' && quote == 2) || (str[i] == '"' && quote == 1) || (str[i] != '\'' && str[i] != '"'))
			{
				cleared = ft_str_p_char(cleared, str[i]);
				j++;
				if (str[i])
					i++;
			}
		}
		if (cleared[j - 1])
			cleared[j] = '\0';
	}
	// else if(quote_checker(str) == 2)
	else
	{
		while (str[i])
		{
			cleared[j] = str[i];
			j++;
			i++;
		}
		cleared[j] = '\0';
	}
	printf("\n%s\n", cleared);
	return (cleared);
}
