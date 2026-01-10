/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framanan <framanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 08:33:10 by framanan          #+#    #+#             */
/*   Updated: 2026/01/08 11:45:16 by framanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_error_export(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '=' && (str[i] != '+' && str[i + 1]))
			return (1);
		i++;
	}
	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (str[i] == '+' && str[i + 1] && str[i + 1] != '=')
			return (1);
		i++;
	}
	return (0);
}

void	ft_export(t_list **curr_env, t_cmd *list)
{
	char	**s;
	char 	**str;
	char 	**env;
	int		i;
	int fd;
	char  *temp;

	i = 1;
	str = list->cmd;
	fd = take_fd(list);
	env = lst_env_to_tab(*curr_env);
	if(count_arg(str) == 1)
	{
		sort_tab(env);
		ft_prin_tab(env, fd);
		return;
	}
	while (str && str[i])
	{
		if (check_error_export(str[i]))
		{
			ft_putstr_fd("export: ", 2);
			ft_putstr_fd(str[i], 2);
			ft_putendl_fd(": not a valid identifier", 2);
			ft_search_replace(curr_env, "?", ft_itoa(1));
			i++;
			continue;
		}
		if (ft_strchr(str[i], '"'))
			str[i] = ft_substr(str[i], 1, (ft_strlen(str[i]) - 2));
		s = ft_split_env(str[i]);
		// if (ft_strchr(str[i], '=') == NULL)
		// {
		// 	i++;
		// 	continue ;
		// }
		temp = ft_strdup(s[0]);
		// if(ft_strchr(str[i], '=') || !s[1][0])
		// 	s[0] = ft_strjoin(s[0], "=");
		if (!s[0][0])
		{
			ft_search_replace(curr_env, "?", ft_itoa(1));
			printf("export: `%s': not a valid identifier\n", str[1]);
			i++;
			continue ;
		}
		if(ft_return_env_value(*curr_env,temp))
			ft_search_replace(curr_env, temp, s[1]);
		else
			env_lst_add_back(curr_env, lstnew(s[0], s[1]));
		i++;
		ft_search_replace(curr_env, "?", ft_itoa(0));
	}
}

void	ft_unset(t_list **curr_env, char **str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		lst_remove(curr_env, str[i]);
		i++;
	}
}

void	ft_cd(t_list **curr_env, char **str)
{
	char	*pwd;
	char *temp;

	temp = NULL;
	pwd = getcwd(NULL, 0);
	if (ft_count_line(str) > 2)
	{
		ft_putendl_fd("bash: cd: too many arguments", 2);
		ft_search_replace(curr_env, "?", ft_itoa(1));
		return ;
	}
	if (ft_count_line(str) == 1)
	{
		chdir(ft_strjoin("/home/", ft_return_env_value(*curr_env, "USER")));
		ft_search_replace(curr_env, "OLDPWD", pwd);
		ft_search_replace(curr_env, "PWD", getcwd(NULL, 0));
		ft_search_replace(curr_env, "?", ft_itoa(0));
		return ;
	}
	if (strcmp(str[1], "~") == 0)
		str[1] = ft_strjoin("/home/", ft_return_env_value(*curr_env, "USER"));
	if(strcmp(str[1], "-") == 0)
	{
		temp = ft_strdup(str[1]);
		str[1] = ft_return_env_value(*curr_env, "OLDPWD");
	}
	if (chdir(str[1]) == 0)
	{
		ft_search_replace(curr_env, "OLDPWD", pwd);
		ft_search_replace(curr_env, "PWD", getcwd(NULL, 0));
		if(temp && strcmp(temp, "-") == 0)
		{
			ft_putendl_fd(getcwd(NULL, 0), 1);
			free(temp);
		}
		ft_search_replace(curr_env, "?", ft_itoa(0));
	}
	else
	{
		ft_putstr_fd("bash : cd : ", 2);
		ft_putstr_fd(str[1], 2);
		ft_putendl_fd(" : No such file or directory", 2);
		ft_search_replace(curr_env, "?", ft_itoa(1));
		return ;
	}
}

char   **sort_tab(char **str)
{
	int i;
	int j;
	char *temp;

	j = 1;
	temp = NULL;

	while(str[j])
	{
		i = 0;
		temp = NULL;
		while(i <= j)
		{
			if(strcmp(str[i], str[j]) > 0)
			{
				temp = str[i];
				str[i] = str[j];
				str[j] = temp;
			}
			i++;
		}
		j++;
	}
	return(str);
}

void  ft_prin_tab(char **str, int fd)
{
	int i;

	i = 0;
	while (str[i])
	{
		if(fd > 0)
		{
			ft_putstr_fd("export ", fd);
			ft_putendl_fd(str[i], fd);
		}
		else
		{
			ft_putstr_fd("export ", 1);
			ft_putendl_fd(str[i], 1);
		}
		i++;
	}
}



void	ft_pwd(t_cmd *lst)
{
	int fd;
	char **str;

	fd = take_fd(lst);
	str = lst->cmd;
	if (strcmp(str[0], "pwd") == 0 && ft_count_line(str) == 1)
	{
		if(getcwd(NULL, 0))
		{
			if(fd > 0)
				ft_putendl_fd(getcwd(NULL, 0), fd);
			else
				ft_putendl_fd(getcwd(NULL, 0), 1);
		}
		else
			ft_putendl_fd("pwd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory", 2);
	}
	else
		ft_putendl_fd("pwd: too many arguments", 2);

}
