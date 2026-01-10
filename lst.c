/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framanan <framanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 22:35:48 by framanan          #+#    #+#             */
/*   Updated: 2026/01/08 11:49:18 by framanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*lstnew(char *name, char *value)
{
	t_list	*lst;

	lst = malloc(sizeof(t_list));
	lst->name = name;
	if (value)
		lst->value = value;
	else
		lst->value = NULL;
	lst->next = NULL;
	return (lst);
}

void	env_lst_add_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	temp = (*lst);
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

void	print_env(t_list *curr_cmd, t_cmd *lst)
{
	int fd;

	fd = take_fd(lst);
	if(lst && lst->cmd && ft_count_line(lst->cmd) > 1)
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(lst->cmd[1], 2);
		ft_putendl_fd(": No such file or directory", 2);
		ft_search_replace(&curr_cmd, "?", ft_itoa(127));
		return;
	}
	else
	{
		while (curr_cmd)
		{
			if(!ft_strcmp(curr_cmd->name, "?") || !curr_cmd->value)
			{
				curr_cmd = curr_cmd->next;
				continue;
			}
			if(fd > 0)
			{
				ft_putstr_fd(curr_cmd->name, fd);
				if (curr_cmd->value)
					ft_putchar_fd('=', fd);
				ft_putendl_fd(curr_cmd->value, fd);
			}
			else
			{
				ft_putstr_fd(curr_cmd->name, 1);
				if (curr_cmd->value)
					ft_putchar_fd('=', 1);
				ft_putendl_fd(curr_cmd->value, 1);
			}
			curr_cmd = curr_cmd->next;
		}
	}
}

void	lst_remove(t_list **lst, char *str)
{
	t_list	*temp;

	temp = *lst;
	while (temp && temp->next)
	{
		if (strcmp(temp->next->name, str) == 0)
		{
			if (temp->next->next)
				temp->next = temp->next->next;
			else
				temp->next = NULL;
		}
		temp = temp->next;
	}
}

char	*ft_return_env_value(t_list *lst, char *name)
{
	if (check_if_cat(name))
	{
		name = ft_substr(name, 0, (ft_strlen(name) - 1));
	}
	while (lst)
	{
		if (strcmp(lst->name, name) == 0)
		{
			if (!(lst->value))
				return (ft_strdup(""));
			return (lst->value);
		}
		lst = lst->next;
	}
	return(NULL);
}
