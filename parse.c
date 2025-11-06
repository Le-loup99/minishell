/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakoto2 <arakoto2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 10:54:52 by arakoto2          #+#    #+#             */
/*   Updated: 2025/11/06 17:09:07 by arakoto2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

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
		i++;
	}
	printf("%d", count);
	return (count);
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
			return ;
		}
		tmp[j] = str[*i];
		j++;
		(*i)++;
	}
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
	while (str[*i] == '<' || str[*i] == '>')
	{
		tmp[j] = str[*i];
		(*i)++;
		j++;
	}
	if (j > 0)
		return (tmp);
	while(str[*i])
	{
		if (tmp[0] && (str[*i] == '\'' || str[*i] == '"') && *i != 0)
		{
			if ((str[(*i) + 1] == ' ' || !str[(*i) + 1]) && str[(*i) - 1] == ' ')
			{
				printf("%s", tmp);
				return (tmp);
			}
			if ((quote == 1 && str[*i] == '\'') || (quote == 2 && str[*i] == '"'))
			{
				quote = 0;
				(*i)++;
			}
			else if (quote == 0 && str[(*i)] == '\'')
			{
				quote = 1;
				(*i)++;
			}
			else if (quote == 0 && str[*i] == '"')
			{
				quote = 2;
				(*i)++;
			}
			else
			{
				tmp[j] = str[(*i)];
				(*i)++;
				j++;
			}
		}
		if (str[*i] == '"' && quote == 0)
		{
			quote = 2;
			(*i)++;
		}
		else if (str[*i] == '\'' && quote == 0)
		{
			quote = 1;
			(*i)++;
		}
		if (str[*i] == '"' && quote == 2)
		{
			if (str[(*i) + 1] == ' ' || str[(*i) + 1] == 0)
			{
				(*i)++;
				printf("%s", tmp);
				return (tmp);
			}
			quote = 0;
			(*i)++;
		}
		else if (str[*i] == '\'' && quote == 1)
		{
			if (str[(*i) + 1] == ' ' || str[(*i) + 1] == 0)
			{
				(*i)++;
				printf("%s", tmp);
				return (tmp);
			}
			quote = 0;
			(*i)++;
		}
		if (str[*i] == '"' && quote == 0)
		{
			quote = 2;
			(*i)++;
		}
		else if (str[*i] == '\'' && quote == 0)
		{
			quote = 1;
			(*i)++;
		}
		if ((str[*i] == ' ' || (str[*i] == '<' || str[*i] == '>')) && quote == 0)
		{
			printf("eto %s", tmp);
			return (tmp);
		}
		/*if ((str[((*i) - 1)] == '\'' || str[(*i) - 1] == '"') || (str[*i] == '<' && str[*i] == '>'))
		{
			if (operator_alone_in_quote(str, (*i) - 1))
			{
				(*i)--;
				get_cmd(str, tmp, i);
			}
		}*/
		if ((str[*i] != '\'' || quote != 1) && (str[*i] != '"' || quote != 2))
		{
			tmp[j] = str[*i];
			j++;
			if (str[*i])
				(*i)++;
		}
	}
	printf("%s", tmp);
	return (tmp);
}

// void	move_index(char *str, int *i, int check)
// {
// 	while(str[*i] == ' ')
// 		(*i)++;
// 	if (str[*i] == '"')
// 	{
// 		(*i)++;
// 		while (str[*i] && str[*i] != '"' && (str[*i] != ' ' || !(check % 2)))
// 			(*i)++;
// 		if (str[*i] && str[(*i) + 1] != ' ' && (str[*i] != ' ' || !(check % 2)))
// 			move_index(str , i, ++check);
// 		if (str[*i] == '"')
// 			(*i) += 1;
// 		return ;
// 	}
// 	else if (str[*i] == '\'')
// 	{
// 		(*i)++;
// 		while (str[*i] && str[*i] != '\'' && (str[*i] != ' ' || !(check % 2)))
// 			(*i)++;
// 		// if (str[*i] && str[(*i) + 1] != ' ')
// 		// 	move_index(str, i, ++check);
// 		if (str[*i] && str[(*i) + 1] != ' ' && (str[*i] != ' ' || !(check % 2)))
// 			move_index(str , i, ++check);
// 		if (str[*i] == '\'')
// 			(*i) += 1;
// 		return ;
// 	}
// 	else
// 	{
// 		while (str[*i] && str[*i] != ' ' && str[*i] != '\'' && str[*i] != '"')
// 			(*i)++;
// 		if (str[*i] == '\'' || str[*i] == '"')
// 			move_index(str, i, ++check);
// 	}
// 	return ;
// }

char **cmd(char *str)
{
	char	*tmp;
	char	**all_cmd;
	int		i;
	int		stock_index;

	stock_index = 0;
	i = 0;
	all_cmd = malloc(sizeof(char *) * count_cmd(str));
	while (str[i])
	{
		tmp = malloc(sizeof(char ) * ft_strlen(str));
		while (str[i] == ' ')
			i++;
		get_cmd(str, tmp, &i);
		printf("%s\n", tmp);
		// move_index(str, &i, 0);
		all_cmd[stock_index] = tmp;
		stock_index++;
	}
	i = 0;
	// while (*all_cmd[i])
	// {
		printf("\n0 = %s", all_cmd[0]);
		printf("\n1 = %s", all_cmd[1]);
		printf("\n2 = %s", all_cmd[2]);
		printf("\n3 = %s", all_cmd[3]);
		printf("\n4 = %s", all_cmd[4]);
		printf("\n5 = %s", all_cmd[6]);
	// 	i++;
	// }
	return(all_cmd);
}
int main()
{
	char *str = "ls'' <''| grep kaiza";
	char *tmp;

	tmp = NULL;
	cmd(str);
}
// "ls -l ''<''| grep kaiza"
// ''