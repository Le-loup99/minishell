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

char *get_cmd(char *str, char *tmp, int index)
{
	int	i;
	int	j;
	int quote;

	i = 0;
	quote = 0;
	j = 0;
	if (tmp)
		free(tmp);
	tmp = malloc (1 * ft_strlen(str) + 1);
	while(str[i])
	{
		if (tmp[0] && (str[i] == '\'' || str[i] == '"'))
		{
			printf("%s", tmp);
			return (tmp);
		}
		if (str[i] == '"' && quote == 0)
		{
			quote = 2;
			index++;
			i++;
		}
		else if (str[i] == '\'' && quote == 0)
		{
			index++;
			quote = 1;
			i++;
		}
		if (str[i] == '"' && quote == 2)
		{
			index++;
			printf("%s", tmp);
			return (tmp);
		}
		else if (str[i] == '\'' && quote == 1)
		{
			index++;
			printf("%s", tmp);
			return (tmp);
		}
		if (str[i] == ' ' && quote == 0)
		{
			index++;
			printf("%s", tmp);
			return (tmp);
		}
		tmp[j] = str[i];
		index++;
		j++;
		i++;
	}
	printf("%s", tmp);
	return (tmp);
}

char *cmd(char *str)
{
	char	*tmp;
	char	**all_cmd;
	int		i;

	i = 0;
	all_cmd = malloc(sizeof(char) * count_cmd(str));
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		tmp = get_cmd(str, tmp, i);
		printf("%s\n", tmp);
	}
}
int main()
{
	char *str = "\"ab\" 'bombo clat'";
	char *tmp;

	tmp = NULL;
	get_cmd(str, tmp, 0);
}