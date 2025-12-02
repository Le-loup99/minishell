/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakoto2 <arakoto2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 12:16:29 by arakoto2          #+#    #+#             */
/*   Updated: 2025/12/02 17:18:04 by arakoto2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_cmd	*ft_lstlast(t_cmd *lst)
// {
// 	while (lst && lst->next)
// 	{
// 		lst = lst->next;
// 	}
// 	return (lst);
// }

// void	ft_lstadd_back(t_cmd **lst, t_cmd *new)
// {
// 	t_cmd	*old_last;

// 	if (!new)
// 		return ;
// 	old_last = ft_lstlast(*lst);
// 	old_last->next = new;
// 	new->next = NULL;
// }

char	ft_strchr(const char *s, int c)
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
		if (ft_strchr(str, '$'))
			return (1);
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
					ft_strcat(cleared, tmp); // verifieo sao dia mi segfault
				else
					cleared[j] = '\0';
				while (cleared[j])
					j++;
			}
			if ((str[i] == '\'' && quote == 2) || (str[i] == '"' && quote == 1) || (str[i] != '\'' && str[i] != '"'))
			{
				cleared[j] = str[i];
				j++;
				if (str[i])
					i++;
			}
		}
		cleared[j] = '\0';
	}
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
