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

char *get_cmd(char *str, char *tmp)
{
	int	i;
	int	j;
	int quote;

	i = 0;
	quote = 0;
	j = 0;
	while(str[i])
	{
		if (tmp[0] && (str[i] == '\'' || str[i] == '"') && i != 0)
		{
			if ((str[i + 1] == ' ' || !str[i + 1]))
			{
				printf("%s", tmp);
				return (tmp);
			}
			quote = 0;
			if (str[i] == '\'' || str[i] == '"')
			{
				if (str[i] == '\'')
					quote = 1;
				else
					quote = 2;
				i++;
			}
		}
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
		{
			if (str[i + 1] == ' ' || str[i + 1] == 0)
			{
				printf("%s", tmp);
				return (tmp);
			}
			i++;
		}
		else if (str[i] == '\'' && quote == 1)
		{
			if (str[i + 1] == ' ' || str[i + 1] == 0)
			{
				printf("%s", tmp);
				return (tmp);
			}
			i++;
		}
		if (str[i] == '"' && quote == 0)
		{
			quote = 2;
			i++;
		}
		// else if (str[i] == '\'' && quote == 0)
		// {
		// 	quote = 1;
		// 	i++;
		// }
		// if (str[i] == ' ' && quote == 0)
		// {
		// 	printf("eto %s", tmp);
		// 	return (tmp);
		// }
		tmp[j] = str[i];
		j++;
		if (str[i])
			i++;
	}
	printf("%s", tmp);
	return (tmp);
}

void	move_index(char *str, int *i)
{
	while(str[*i] == ' ')
		(*i)++;
	if (str[*i] == '"')
	{
		(*i)++;
		while (str[*i] && str[*i] != '"')
			(*i)++;
		(*i) += 1;
		return ;
	}
	else if (str[*i] == '\'')
	{
		(*i)++;
		while (str[*i] && str[*i] != '\'')
			(*i)++;
		return ;
	}
	else
	{
		while (str[*i] && str[*i] != ' ' && str[*i] != '\'' && str[*i] != '"')
			(*i)++;
	}
	return ;
}

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
		get_cmd(str + i, tmp);
		printf("%s\n", tmp);
		move_index(str, &i);
		all_cmd[stock_index] = tmp;
		stock_index++;
	}
	i = 0;
	while (*all_cmd[i])
	{
		printf("\n%s", all_cmd[i]);
		i++;
	}
	return(all_cmd);
}
int main()
{
	char *str = "\"ab\" kozy' bombo clat'";
	char *tmp;

	tmp = NULL;
	cmd(str);
}

// next test id ""kozy\" kaiza\" 