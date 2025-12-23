/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakoto2 <arakoto2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 10:54:52 by arakoto2          #+#    #+#             */
/*   Updated: 2025/12/23 11:13:18 by arakoto2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <string.h>

int count_cmd(char *str)
{
	int	i;
	int	count;
	int quote;

	i = 0;
	count = 1;
	quote = 0;
	while (str[i] == ' ')
		i++;
	if (!str[i])
		count = 0;
	while (str[i])
	{
		if (str[i] == '"' && quote == 0)
		{
			quote = 2;
			i++;
		}
		else if (str[i] == '\'' && quote == 0)
		{
			quote = 1;
			i++;
		}
		if (str[i] == '"' && quote == 2)
			quote = 0;
		else if (str[i] == '\'' && quote == 1)
			quote = 0;
		if (str[i] == ' ' && str[i + 1] != ' ' && str[i + 1] != 0
			&& quote == 0)
			count++;
		if ((str[i] == '|' || str[i] == '<' || str[i] == '>' || str[i] == '(' || str[i] == ')') && quote == 0)
			count+= 2;
		i++;
	}
	return (count + 1);
}

// int ft_strlen(char *str)
// {
// 	int	i;

// 	i= 0;
// 	while (str && str[i])
// 		i++;
// 	return (i);
// }

int	 operator_alone_in_quote(char *str, int i)
{
	if(str[i] == '\'' && (str[i + 1] == '<' || str[i + 1] == '>'))
	{
		if (str[i + 2] == '\'' && (str[i + 3] == ' ' || str[i + 3] == 0))
			return (1);
		else if((str[i + 2] == '<' || str[i + 2] == '>') && (str[i + 3] == '\'') && (str[i + 4] == ' ' || str[i + 4] == 0))
			return (1);
	}
	else if(str[i] == '"' && (str[i + 1] == '<' || str[i + 1] == '>'))
	{
		if (str[i + 2] == '"' && (str[i + 3] == ' ' || str[i + 3] == 0))
			return (1);
		else if((str[i + 2] == '<' || str[i + 2] == '>') && (str[i + 3] == '"') && (str[i + 3] == ' ' || str[i + 3] == 0))
			return (1);
	}
	return (0);
}

void copy_operator_in_quote(char *str, char *tmp, int *i)
{
	int	j;

	j = 0;
	tmp[j] = str[*i];
	(*i)++;
	j++;
	while (j < 4)
	{
		if (str[*i] == tmp[0])
		{
			tmp[j] = str[*i];
			(*i)++;
			tmp[j + 1] = '\0';
			return ;
		}
		tmp[j] = str[*i];
		j++;
		(*i)++;
	}
	tmp[j + 1] = '\0';
	return ;
}

char *get_cmd(char *str, char *tmp, int *i)
{
	int	j;
	int quote;

	quote = 0;
	j = 0;
	if (operator_alone_in_quote(str, (*i)))
	{
		copy_operator_in_quote(str, tmp, i);
		return (tmp);
	}
	if (str[*i] == '<' || str[*i] == '>')
	{
		while ((str[*i] == '<' || str[*i] == '>') && j < 2)
		{
			tmp[j] = str[*i];
			(*i)++;
			j++;
		}
		tmp[j] = '\0';
	}
	else if (str[*i] == '|' && j < 2)
	{
		while(str[*i] == '|' && j < 2)
		{
			tmp[j] = str[*i];
			(*i)++;
			j++;
		}
		tmp[j] = '\0';
	}
	else if ((str[*i] == '(' || str[*i] == ')') && j < 2)
	{
		tmp[j] = str[*i];
		(*i)++;
		j++;
	}
	if (j > 0)
		return (tmp);
	while(str[*i])
	{
		if ((str[*i] == '\'' || str[*i] == '"') && *i != 0)
		{
			if ((str[(*i) + 1] == ' ' || !str[(*i) + 1]) && str[(*i) - 1] == ' ' && quote == 0)
			{
				tmp[j + 1] = '\0';
				// printf("%s", tmp);
				return (tmp);
			}
			if ((quote == 1 && str[*i] == '\'') || (quote == 2 && str[*i] == '"'))
			{
				quote = 0;
				tmp[j] = str[*i];
				j++;
				if (str[*i])
					(*i)++;
			}
			else if (quote == 0 && str[(*i)] == '\'')
			{
				quote = 1;
				tmp[j] = str[*i];
				j++;
				if (str[*i])
					(*i)++;
			}
			else if (quote == 0 && str[*i] == '"')
			{
				quote = 2;
				tmp[j] = str[*i];
				j++;
				if (str[*i])
					(*i)++;
			}
			else
			{
				tmp[j] = str[*i];
				j++;
				if (str[*i])
					(*i)++;
			}
		}
		if (str[*i] == '"' && quote == 0)
		{
			quote = 2;
		}
		else if (str[*i] == '\'' && quote == 0)
		{
			quote = 1;
		}
		else if (str[*i] == '"' && quote == 2)
		{
			if (str[(*i) + 1] == ' ' || str[(*i) + 1] == 0)
			{
				tmp[j] = str[*i];
				j++;
				if (str[*i])
					(*i)++;
				// printf("%s", tmp);
				tmp[j] = '\0';
				return (tmp);
			}
			quote = 0;
		}
		else if (str[*i] == '\'' && quote == 1)
		{
			if (str[(*i) + 1] == ' ' || str[(*i) + 1] == 0)
			{
				tmp[j] = str[*i];
				j++;
				if (str[*i])
					(*i)++;
				tmp[j] = '\0';
				// printf("%s", tmp);
				return (tmp);
			}
			quote = 0;
		}
		if ((str[*i] == ' ' || (str[*i] == '<' || str[*i] == '>' || str[*i] == '|'
			|| str[*i] == '(' || str[*i] == ')')) && quote == 0)
		{
			tmp[j] = '\0';
			// printf("eto %s", tmp);
			return (tmp);
		}
		if (*i != 0 && ((str[((*i) - 1)] == '\'' || str[(*i) - 1] == '"') || (str[*i] == '<' && str[*i] == '>'))) //teto nisy napiko
		{
			if (operator_alone_in_quote(str, (*i) - 1))
			{
				(*i)--;
				get_cmd(str, tmp, i);
			}
		}
		tmp[j] = str[*i];
		j++;
		if (str[*i])
			(*i)++;
	}
	tmp[j] = '\0';
	// printf("%s", tmp);
	return (tmp);
}

char **cmd(char *str)
{
	char	*tmp;
	char	**all_cmd;
	int		i;
	int		stock_index;
	char	**cleared;
	int		check_split_expand;
	int		j;

	stock_index = 0;
	i = 0;
	check_split_expand = 0;
	j = 0;
	all_cmd = malloc(sizeof(char *) * (count_cmd(str)));
	cleared = malloc(sizeof(char *) * (count_cmd(str)));
	tmp = NULL;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (!str[i])
			break;
		tmp = malloc(sizeof(char ) * ft_strlen(str) + 1 + 1);
		get_cmd(str, tmp, &i);
		// printf("%s\n", tmp);
		all_cmd[stock_index] = tmp;
		stock_index++;
	}
	all_cmd[stock_index] = NULL;
	i = 0;
	while (i  < count_cmd(str) && all_cmd[i])
	{
		if (!ft_strchr(all_cmd[i], '$'))
			cleared[j] = malloc(sizeof(char ) * ft_strlen(all_cmd[i]) + 1);
		else
		{
			cleared[j] = malloc(sizeof(char) * calcul_env_size(all_cmd[i]) + 1);
			if (!cleared)
				return(NULL);
			cleared[j][0] = '\0';
		}
			// printf("\n%d = %s\n", i, all_cmd[i]);
		cleared[j][0] = '\0';
		tmp = ft_strdup(all_cmd[i]);
		cleared[j] = quote_clearer(&(all_cmd[i]), cleared[j],&check_split_expand);
		while (check_split_expand == 1)
		{
			j++;
			if (!ft_strchr(all_cmd[i], '$'))
				cleared[j] = malloc(sizeof(char ) * ft_strlen(all_cmd[i]) + 1);
			else
			{
				cleared[j] = malloc(sizeof(char) * calcul_env_size(all_cmd[i]) + 1);
				if (!cleared)
					return(NULL);
				cleared[j][0] = '\0';
			}
			cleared[j] = quote_clearer(&(all_cmd[i]), cleared[j], &check_split_expand);
			i++;
		}
		j++;
		i++;
	}
	free_pp(all_cmd);
	if (all_cmd)
		free(all_cmd);
	cleared[i] = NULL;
	return(cleared);
}


int main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;
	t_cmd *lst;
	char **stock;
	char *str;
	// char **all_path;
	char *path = NULL;
	int fd[2];
	int fd_temp;
	pid_t pid = 0;

	lst = NULL;
	fd_temp = 0;
	// all_path = take_path(env);
	while ((str = readline("minishell> ")))
	{
		if (check_error_at_end(str) >= 0 && check_quote_error(str) >= 0 && check_operator_error(str) >= 0)
		{
			stock = cmd(str);
			cmd_to_lst(stock , &lst);
			int size = ft_cmd_size(lst);
			ft_heredoc(lst);
			ft_execution(lst, env, fd_temp, path, fd, pid, size);
			free(str);
			str = NULL;
			lst = NULL;
			// print_lst(lst);
		}
	}
	// free_pp(stock);
	// free(stock);
	// free(lst);
}
