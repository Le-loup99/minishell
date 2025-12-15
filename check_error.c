/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakoto2 <arakoto2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 09:31:04 by arakoto2          #+#    #+#             */
/*   Updated: 2025/12/15 11:52:59 by arakoto2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_error_at_end(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i] == ' ')
		i++;
	if (str[i] == '|')
	{
		printf("syntax error near unexpected token `|'\n");
		return (-1);
	}
	while (str[i])
		i++;
	while (!str[i] || str[i] == ' ')
		i--;
	if (str[i] == '|' || str[i] == '<' || str[i] == '>')
	{
		if (str[i] == '|')
			printf("syntax error near unexpected token `|'\n");
		else if(str[i] == '>' || '<')
			printf("syntax error near unexpected token `newline'\n");
		return (-1);
	}
	return (0);
}

int	check_quote_error(char *str)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '\'' && quote == 0)
			quote = 1;
		else if (str[i] == '"' && quote == 0)
			quote = 2;
		else if(str[i] == '\'' && quote == 1)
			quote = 0;
		else if (str[i] == '"' && quote == 2)
			quote = 0;
		i++;
	}
	if (quote != 0)
	{
		printf("syntax error quote is not closed");
		return (-1);
	}
	return (0);
}

int	check_space(char *str, int *i)
{
	int	space;

	space = 0;
	while(str[(*i)] && str[(*i)] == ' ')
	{
		(*i)++;
		space = 1;
	}
	return (space);
}

/*void error_message(char *to_compare)
{
	if (!ft_strcmp(to_compare, ">"))
	{
		printf("syntax error near unexpected token `>'");
	}
	else if (!ft_strcmp(to_compare, "<"))
	{
		printf("syntax error near unexpected token `<'");
	}
	else if (!ft_strcmp(to_compare, "|"))
	{
		printf("syntax error near unexpected token `|'");
	}
	else if (!ft_strcmp(to_compare, "<<"))
	{
		printf("syntax error near unexpected token `<<'");
	}
	else if (!ft_strcmp(to_compare, ">>"))
	{
		printf("syntax error near unexpected token `>>'");
	}
	else if (!ft_strcmp(to_compare, "<>"))
	{
		printf("syntax error near unexpected token `<>'");
	}
	else if (!ft_strcmp(to_compare, ">|"))
	{
		printf("syntax error near unexpected token `>|'");
	}
	return ;
}*/

int	check_operator_nbr(char *str, int i)
{
	int	count;

	count = 0;
	while(str[i] && (str[i] == '|' || str[i] == '>' || str[i] == '<'))
	{
		i++;
		count++;
	}
	return (count);
}

int	check_operator_error(char *str)
{
	int	i;
	int	space;

	i = 0;
	space = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		check_space(str, &i);
		if (!str[i])
			return (0);
		if (str[i] == '>')
		{
			// check += 1;
			if (check_operator_nbr(str, i) > 2)
			{
				printf("syntax error\n");
				return (-1);
			}
			i++;
			space = check_space(str, &i);
			if (space != 0 && (str[i] == '|' || str[i] == '<' || str[i] == '>'))
			{
				printf("syntax error\n");
				return (-1);
			}
			else if(space == 0 && str[i] == '<')
			{
				printf("syntax error\n");
				return (-1);
			}
		}
		else if (str[i] == '<')
		{
			if (check_operator_nbr(str, i) > 2)
			{
				printf("syntax error\n");
				return (-1);
			}
			i++;
			space = check_space(str, &i);
			if (space != 0 && (str[i] == '|' || str[i] == '<' || str[i] == '>'))
			{
				printf("syntax error\n");
				return (-1);
			}
			else if (space == 0 && (str[i] == '|'))
			{
				printf("syntax error\n");
				return (-1);
			}
		}
		else if(str[i] == '|')
		{
			if (check_operator_nbr(str, i) > 2)
			{
				printf("syntax error\n");
				return (-1);
			}
			i++;
			space = check_space(str, &i);
			if (space != 0 && (str[i] == '|' || str[i] == '<' || str[i] == '>'))
			{
				printf("syntax error\n");
				return (-1);
			}
		}
		space = 0;
		i++;
	}
	return (0);
}
