/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakoto2 <arakoto2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 14:28:52 by arakoto2          #+#    #+#             */
/*   Updated: 2026/01/09 21:14:21 by arakoto2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand(char **str, char *cleared, int not_first, t_list *env)
{
	int		i;
	int		quote;
	char	*tmp;
	int		j;

	j = 0;
	tmp = NULL;
	quote = 0;
	i = 0;
	j = 0;
	// cleared = malloc (1);
	// if (!cleared)
	// 	cleared = NULL;
	cleared = NULL;
	while (*str && (*str)[i])
	{
		if ((*str)[i] == '\'' && quote == 0)
		{
			quote = 1;
			cleared = ft_str_p_char(cleared, (*str)[i]);
			j++;
			if ((*str)[i])
				i++;
			else
				break ;
		}
		else if ((*str)[i] == '"' && quote == 0)
		{
			quote = 2;
			cleared = ft_str_p_char(cleared, (*str)[i]);
			j++;
			if ((*str)[i])
				i++;
			else
				break ;
		}
		if ((*str)[i] == '\'' && quote == 1)
		{
			quote = 0;
			cleared = ft_str_p_char(cleared, (*str)[i]);
			j++;
			if ((*str)[i])
				i++;
			else
				break ;
		}
		else if ((*str)[i] == '"' && quote == 2)
		{
			quote = 0;
			cleared = ft_str_p_char(cleared, (*str)[i]);
			j++;
			if ((*str)[i])
				i++;
			else
				break ;
		}
		if ((*str)[i] == '$' && quote != 1 && (not_first == 0
				|| ft_strcmp(str[-1], "<<")))
		{
			// cleared[j] = '\0';
			tmp = converter(*str, &i, env);
			if (tmp)
				cleared = ft_strjoin(cleared, tmp);
		}
		cleared = ft_str_p_char(cleared, (*str)[i]);
		j++;
		if ((*str)[i])
			i++;
	}
	return (cleared);
}

char	**expand_all(char **all_cmd, char **cleared, t_list *env)
{
	int	i;

	i = 0;
	while (all_cmd && all_cmd[i])
	{
		// cleared[i][0] = '\0';
		cleared[i] = expand(&(all_cmd[i]), cleared[i], i, env);
		i++;
	}
	cleared[i] = NULL;
	return (cleared);
}

