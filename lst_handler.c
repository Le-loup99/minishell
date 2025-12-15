/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakoto2 <arakoto2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 12:36:00 by arakoto2          #+#    #+#             */
/*   Updated: 2025/12/15 13:25:11 by arakoto2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_cmd *nwlst(char *cmd)
// {
// 	t_cmd	*new;

// 	new = malloc (sizeof(t_cmd));
// 	new->cmd = cmd;
// 	new->next = NULL;
// 	return (new);
// }
t_redir	*new_redir(char *type, char *target)
{
	t_redir *new_redir;

	new_redir = malloc (sizeof(t_redir));
	new_redir->type = type;
	new_redir->target = target;
	new_redir->redir_next = NULL;
	return (new_redir);
}

t_redir	*last_redir(t_redir *redir)
{
	while(redir && redir->redir_next)
	{
		redir = redir->redir_next;
	}
	return (redir);
}

void	redir_add_back(t_redir *redir, t_redir *new)
{
	redir = last_redir(redir);
	if (!new)
		return ;
	redir->redir_next = new;
}

t_redir	*implement_redir(t_cmd **argv, int *i)
{
	t_redir	*final;
	t_redir *tmp;

	final = NULL;
	tmp = NULL;
	while (argv[(*i)] && argv[(*i)] != '|')
	{
		if (!final)
			final = new_redir(argv[(*i)], argv[++(*i)]);
		else
			tmp = new_redir(argv[(*i)], argv[++(*i)]);
		if (tmp)
			redir_add_back(final, tmp)
	}
	return (final);
}

t_cmd *nwlst(char **argv, int *i)
{
	t_cmd	*new;

	new = malloc (sizeof(t_cmd));
	while (argv[(*i)])
	{
		if (!ft_strcmp(argv[(*i)], "<") || !ft_strcmp(argv[(*i)] , "<<")
			|| !ft_strcmp(argv[(*i)], ">") || !ft_strcmp(argv[(*i)] , ">>"))
		{
			implement_redir(argv, i);
		}
		if (!ft_strcmp(argv[(*i)], "|"))
		{
			++(*i);
			return (new);
		}
		else ()
	}
	return (new);
}

t_cmd *lst_last(t_cmd *lst)
{
	while(lst && lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

void lst_add_back(t_cmd *lst, t_cmd *new)
{
	lst = lst_last(lst);
	if (!new)
		return ;
	lst->next = new;
	new->next = NULL;
}

void print_lst(t_cmd *lst)
{
	while (lst && lst->cmd)
	{
		if (lst->cmd)
			printf("%s\n", lst->cmd);
		if (lst->next)
			lst = lst->next;
		else
			break;
	}
}

t_cmd **cmd_to_lst(char **cmd, t_cmd **lst)
{
	int		i;
	t_cmd	*tmp;

	i = 0;
	tmp = NULL;
	while (cmd && cmd[i])
	{
		if (i == 0)
		{
			(*lst) = nwlst(cmd, &i);
		}
		else
		{
			tmp = nwlst(cmd + i, &i);
		}
		if (tmp)
		{
			lst_add_back((*lst), tmp);
		}
		i++;
	}
	return (lst);
}

// int main()
// {
// 	t_cmd *head;
// 	t_cmd *second;
// 	t_cmd *third;

// 	head = nwlst("test");
// 	second = nwlst("is it");
// 	third = nwlst("troisgedy");
// 	lst_add_back(head, second);
// 	lst_add_back(head, NULL);
// 	lst_add_back(head, nwlst("troitroi"));
// 	print_lst(head);	
// }
