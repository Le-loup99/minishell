/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakoto2 <arakoto2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 12:16:29 by arakoto2          #+#    #+#             */
/*   Updated: 2026/01/09 21:09:20 by arakoto2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	else if ((!s1 && s2) || (!s2 && s1))
		return (4);
	while (s1 && s2 && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (s1 && s2 && ((!s1[i] && s2[i]) || (s1[i] && !s2[i])))
		return (20);
	return (0);
}
// static int	check_space(char *str)
// {
// 	int	i;

// 	i = 0;
// 	if (str)
// 		return (0);
// 	while(str[i])
// 	{
// 		if (str[i] == ' ')
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }
// int	ft_strchr(const char *s, int c)
// {
// 	int		i;
// 	char	*stock;

// 	stock = (char *) s;
// 	i = 0;
// 	while (stock[i] != '\0')
// 	{
// 		if ((unsigned char)stock[i] == (unsigned char)c)
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

int	quote_checker(char *str)
{
    int	i;

	i = 0;
	if (str[i] == '\'')
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
	if (!s1)
		final = malloc (2);
	else
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

char	*ft_strjoin_pars(char *dst, char *src)
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

int	check_space(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

// char	*tmp_cuter(char *tmp)
// {
// 	char	*cuted;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	if (!tmp)
// 		return (NULL);
// 	cuted = malloc (ft_strlen(tmp) + 1);
// 	while (tmp[i] && (tmp[i] == ' ' || tmp[i] == '\t'))
// 		i++;
// 	while (tmp[i] && tmp[i] != ' ')
// 	{
// 		cuted[j] = tmp[i];
// 		i++;
// 		j++;
// 	}
// 	cuted[j] = '\0';
// 	// free (tmp);
// 	return (cuted);
// }

// char	*str_cuter(char	*str, char *tmp, t_list *env)
// {
// 	int		i;
// 	int		j;
// 	char	*stock;
// 	char	*to_add;
// 	int		check_split_expand;
// 	char	*new_str;

// 	i = 0;
// 	j = 0;
// 	check_split_expand = 0;
// 	to_add = NULL;
// 	new_str = NULL;
// 	if (!tmp)
// 		return (NULL);
// 	stock = malloc (ft_strlen(tmp) + 1);
// 	if (!stock)
// 		return (NULL);
// 	if (tmp[0] && (tmp[0] == ' ' || tmp[0] == '\t'))
// 	{
// 		while (tmp[j] == ' ' || tmp[j] == '\t')
// 			j++;
// 	}
// 	while (tmp[j] && tmp[j] != ' ' && tmp[j] != '\t')
// 		j++;
// 	while (tmp[j] && (tmp[j] == ' ' || tmp[j] == '\t'))
// 		j++;
// 	// ft_strlcpy(stock, tmp + j, 	INT_MAX);
// 	while (tmp[j])
// 	{
// 		stock[i] = tmp[j];
// 		i++;
// 		if (tmp[j] == ' ' || tmp[j] == '\t')
// 		{
// 			while (tmp[j] == ' ' || tmp[j] == '\t')
// 				j++;
// 		}
// 		else
// 			j++;
// 	}
// 	stock[i] = '\0';
// 	j = 0;
// 	while(str[j] && str[j] != '"' && str[j] != '\'')
// 		j++;
// 	if (str[j] == '"' || str[j] == '\'')
// 	{
// 		if (!ft_strchr(str + j, '$'))
// 		{
// 			to_add = malloc(sizeof(char ) * ft_strlen(str) + 1);
// 			if (!to_add)
// 				return(NULL);
// 			to_add[0] = '\0';
// 		}
// 		else
// 		{
// 			to_add = malloc(sizeof(char) * calcul_env_size(str) + 1);
// 			if (!to_add)
// 				return(NULL);
// 			to_add[0] = '\0';
// 		}
// 		new_str = ft_strdup(str + j);
// 			// printf("\n%d = %s\n", i, all_cmd[i]);
// 		to_add = quote_clearer(&new_str, to_add,&check_split_expand, 0, env);
// 	}
// 	if (to_add)
// 		stock = ft_strjoin_pars(stock, to_add);
// 	else
// 		stock[i] = '\0';
// 	free(to_add);
// 	// if (str)
// 	// 	free(str);
// 	return (stock);
// }

// char	*str_space_cuter(char	*str, char *tmp)
// {
// 	int		i;
// 	int		j;
// 	char	*stock;
// 	char	*to_add;
// 	int		check_split_expand;
// 	char	*new_str;

// 	(void )str;
// 	i = 0;
// 	j = 0;
// 	check_split_expand = 0;
// 	to_add = NULL;
// 	new_str = NULL;
// 	if (!tmp)
// 		return (NULL);
// 	stock = malloc (ft_strlen(tmp) + 1);
// 	if (!stock)
// 		return (NULL);
// 	if (tmp[0] && (tmp[0] == ' ' || tmp[0] == '\t'))
// 	{
// 		while (tmp[j] == ' ' || tmp[j] == '\t')
// 			j++;
// 	}
// 	while (tmp[j] && tmp[j] != ' ' && tmp[j] != '\t')
// 		j++;
// 	while (tmp[j] && (tmp[j] == ' ' || tmp[j] == '\t'))
// 		j++;
// 	while (tmp[j])
// 	{
// 		stock[i] = tmp[j];
// 		i++;
// 		if (tmp[j] == ' ' || tmp[j] == '\t')
// 		{
// 			while (tmp[j] == ' ' || tmp[j] == '\t')
// 				j++;
// 		}
// 		else
// 			j++;
// 	}
// 	stock[i] = '\0';
// 	return (stock);
// }

char	*quote_clearer(char **str, char *cleared, int	*check_split_expand, int not_first, t_list *env)
{
	int		quote;
	int		i;
	int		j;

	(void) env;
	(void) not_first;
	j = 0;
	i = 0;
	quote = 0;
	if (!str)
		return (NULL);
	if (!quote_checker(*str))
	{
		while (*str && (*str)[i])
		{
			if((*str)[i] == '\'' && quote == 0)
			{
				quote = 1;
				i++;
			}
			else if ((*str)[i] == '"' && quote == 0)
			{
				quote = 2;
				i++;
			}
			if ((*str)[i] == '\'' && quote == 1)
			{
				quote = 0;
				i++;
			}
			else if ((*str)[i] == '"' && quote == 2)
			{
				quote = 0;
				i++;
			}
			else if (((*str)[i] == '\'' && quote == 2) || ((*str)[i] == '"' && quote == 1) || ((*str)[i] != '\'' && (*str)[i] != '"'))
			{
				cleared = ft_str_p_char(cleared, (*str)[i]);
				j++;
				if ((*str)[i])
					i++;
			}
		}
		if (cleared[j - 1])
			cleared[j] = '\0';
	}
	else
	{
		while ((*str)[i])
		{
			cleared[j] = (*str)[i];
			j++;
			i++;
		}
		cleared[j] = '\0';
	}
	*check_split_expand = 0;
	return (cleared);
}
