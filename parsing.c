/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakoto2 <arakoto2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 18:05:23 by arakoto2          #+#    #+#             */
/*   Updated: 2026/01/09 21:17:01 by arakoto2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_space(char **expanded ,int size)
{
	char	**splited;
	int		splt_i;
	int		splt_j;
	int		i;
	int		j;
	int		quote;

	quote = 0;
	j = 0;
	i = 0;
	splt_i = 0;
	splt_j = 0;
	if (!expanded)
		return (NULL);
	splited = malloc(sizeof(char *) * (size));
	while (expanded[i])
	{
		splt_j = 0;
		splited[splt_i] = malloc(ft_strlen(expanded[i]) + 1);
		while (expanded[i][j] && (expanded[i][j] != ' ' || quote != 0))
		{
			if (expanded[i][j] == '\'' && quote == 0)
				quote = 1;
			else if (expanded[i][j] == '\'' && quote == 1)
				quote = 0;
			else if (expanded[i][j] == '"' && quote == 0)
				quote = 2;
			else if (expanded[i][j] == '"' && quote == 2)
				quote = 0;
			splited[splt_i][splt_j] = expanded[i][j];
			j++;
			splt_j++;
		}
		if (expanded[i][j] == ' ')
		{
			splt_i++;
			j++;
			while (expanded[i][j] && expanded[i][j] == ' ')
				j++;
			if (!expanded[i][j])
			{
				printf("\nniditra\n");
				i++;
				j = 0;
			}
		}
		else
		{
			splited[splt_i][splt_j] = '\0';
			splt_i++;
			i++;
			j = 0;
		}
	}
	splited[splt_i] = NULL;
	return (splited);
}

char	**cmd(char *str, t_list *env)
{
	char	**all_cmd;
	char	**cleared;
	char	**expanded;
	char	**splited;
	int		i;
	int		j;
	int		check_split_expand;

	j = 0;
	cleared = NULL;
	all_cmd = tokenisation(str);
	expanded = malloc(sizeof(char *) * (count_cmd(str) + 1));
	expanded = expand_all(all_cmd, expanded, env);
	splited = split_space(expanded, count_cmd(str) + 1);
	if (splited)
		cleared = malloc(sizeof(char *) * (ft_count_line(splited) + 1));
	if (all_cmd)
	{
		free (all_cmd);
		all_cmd = NULL;
	}
	all_cmd = expanded;
	i = 0;
	while (splited && splited[i])
	{
			cleared[j] = malloc(sizeof(char ) * ft_strlen(splited[i]) + 1);
			if (!cleared[j])
				return(NULL);
			cleared[j][0] = '\0';
		cleared[j][0] = '\0';
		if (i > 0 && !ft_strcmp(splited[i - 1], "<<"))
		{
			free(cleared[j]);
			cleared[j] = ft_strdup(splited[i]);
		}
		else
			cleared[j] = quote_clearer(&(splited[i]), cleared[j],&check_split_expand, j, env);
		j++;
		i++;
	}
	// free_pp(all_cmd);
	if (all_cmd)
		free(all_cmd);
	cleared[j] = NULL;
	return(cleared);
}
