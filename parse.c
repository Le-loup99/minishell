/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakoto2 <arakoto2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 10:54:52 by arakoto2          #+#    #+#             */
/*   Updated: 2025/12/09 16:22:08 by arakoto2         ###   ########.fr       */
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

int ft_strlen(char *str)
{
	int	i;

	i= 0;
	while (str && str[i])
		i++;
	return (i);
}

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
		printf("niditra");
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
				printf("%s", tmp);
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
				printf("%s", tmp);
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
				printf("%s", tmp);
				return (tmp);
			}
			quote = 0;
		}
		if ((str[*i] == ' ' || (str[*i] == '<' || str[*i] == '>' || str[*i] == '|'
			|| str[*i] == '(' || str[*i] == ')')) && quote == 0)
		{
			tmp[j] = '\0';
			printf("eto %s", tmp);
			return (tmp);
		}
		if ((str[((*i) - 1)] == '\'' || str[(*i) - 1] == '"') || (str[*i] == '<' && str[*i] == '>'))
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
	printf("%s", tmp);
	return (tmp);
}

char **cmd(char *str)
{
	char	*tmp;
	char	**all_cmd;
	int		i;
	int		stock_index;
	char	**cleared;

	stock_index = 0;
	i = 0;
	all_cmd = malloc(sizeof(char *) * (count_cmd(str)));
	cleared = malloc(sizeof(char *) * (count_cmd(str)));
	tmp = NULL;
	while (str[i])
	{
		tmp = malloc(sizeof(char ) * ft_strlen(str) + 1 + 1);
		while (str[i] == ' ')
			i++;
		get_cmd(str, tmp, &i);
		printf("%s\n", tmp);
		all_cmd[stock_index] = tmp; // mila soloina
		stock_index++;
	}
	all_cmd[stock_index] = NULL;
	i = 0;
	while (i  < count_cmd(str) && all_cmd[i])
	{
		if (!ft_strchr(all_cmd[i], '$'))
			cleared[i] = malloc(sizeof(char ) * ft_strlen(all_cmd[i]) + 1);
		else
		{
			cleared[i] = malloc(sizeof(char) * calcul_env_size(all_cmd[i]) + 1);
			if (!cleared)
				return(NULL);
			cleared[i][0] = '\0';
		}
			printf("\n%d = %s\n", i, all_cmd[i]);
		cleared[i][0] = '\0';
		cleared[i] = quote_clearer(all_cmd[i], cleared[i]); // aza adino no manova fonction an'ilay maka liste
		i++;
		// printf(" %d ", quote_handler(all_cmd[0]));
	}
	free_pp(all_cmd);
	if (all_cmd)
		free(all_cmd);
	cleared[i] = NULL;
	return(cleared);
}

int main()
{
	t_cmd *lst;
	char **stock;
	char *str = "echo \"a 'b' c\"' d \"e\" f' g\"h 'i' j\"k";
	lst = NULL;
	printf("\n[%d]\n", count_cmd(str));

	// tmp = NULL;
	stock = cmd(str);
	cmd_to_lst(stock , &lst);
	printf("\n\n");
	print_lst(lst);
	free_pp(stock); // ito alana
	free(stock);
	free(lst);
}
// eto||||()() grep kaiza
// "ls -l ''<''| grep kaiza"
// ''
// 'kaiza' \"\"\"lesy\" 
// (), >, |, ||
// kaiza \"<\"lesy
// char *str = "echo \"hello;world\" '&&' foo|bar";
// char *str = "echo \"a 'b' c\"' d \"e\" f' g\"h 'i' j\"k";
// "test \"hello;world\" '&&'foo|bar"
// 	char *str = "$USER$ZSH"; ETO NDRAY ALOHA