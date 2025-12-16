/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakoto2 <arakoto2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 12:36:00 by arakoto2          #+#    #+#             */
/*   Updated: 2025/12/16 15:20:56 by arakoto2         ###   ########.fr       */
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
	if (!ft_strcmp(type, "<"))
		new_redir->type = IN;
	else if (!ft_strcmp(type, ">"))
		new_redir->type = OUT;
	else if (!ft_strcmp(type, ">>"))
		new_redir->type = APPEND;
	else if (!ft_strcmp(type, "<<"))
		new_redir->type = HEREDOC;
	new_redir->file_name = target;
	new_redir->fd = -1;
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

t_redir	*implement_redir(char **argv, int *i)
{
	t_redir	*final;
	t_redir *tmp;

	final = NULL;
	tmp = NULL;
	while (argv[(*i)] && ft_strcmp(argv[(*i)], "|"))
	{
		if (!final)
			final = new_redir(argv[(*i)], argv[++(*i)]);
		else
			tmp = new_redir(argv[(*i)], argv[++(*i)]);
		if (tmp)
			redir_add_back(final, tmp);
		(*i)++;
		if (ft_strcmp(argv[(*i)], ">>") && ft_strcmp(argv[(*i)], ">")
			&& ft_strcmp(argv[(*i)], "<<") && ft_strcmp(argv[(*i)], "<"))
			break;
		tmp = NULL;
	}
	return (final);
}

int	ft_is_builting(char *str)
{
	if (!ft_strcmp(str, "echo"))
		return (1);
	else if (!ft_strcmp(str, "cd"))
		return (1);
	else if (!ft_strcmp(str, "pwd"))
		return (1);
	else if (!ft_strcmp(str, "export"))
		return (1);
	else if (!ft_strcmp(str, "unset"))
		return (1);
	else if (!ft_strcmp(str, "env"))
		return (1);
	else if (!ft_strcmp(str, "exit"))
		return (1);
	return (0);
}

t_cmd *nwlst(char **argv, int *i)
{
	t_cmd	*new;
	int		cmd_index;

	cmd_index = 0;
	new = malloc (sizeof(t_cmd));
	new->cmd = malloc (sizeof(char *) + 50);
	new->redir = NULL;
	// new->in = NULL;
	// new->out = NULL;
	while (argv[(*i)])
	{
		if (!ft_strcmp(argv[(*i)], "<") || !ft_strcmp(argv[(*i)] , "<<")
			|| !ft_strcmp(argv[(*i)], ">") || !ft_strcmp(argv[(*i)] , ">>"))
		{
			new->redir = implement_redir(argv, i);
		}
		else if (!ft_strcmp(argv[(*i)], "|"))
		{
			(*i)++;
			new->next = NULL;
			new->cmd[cmd_index] = NULL;
			return (new);
		}
		else
		{
			new->is_builtin = ft_is_builting(argv[(*i)]);
			new->cmd[cmd_index] = argv[(*i)];
			cmd_index++;
			(*i)++;
		}
	}
	new->cmd[cmd_index] = NULL;
	new->next = NULL;
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

void lst_add_back(t_cmd **lst, t_cmd *new)
{
	t_cmd *tmp;

	tmp = *lst;
	// tmp = lst_last(tmp);
	while(tmp && tmp->next)
	{
		tmp = tmp->next;
	}
	// if (!new)
	// 	return ;
	tmp->next = new;
}

t_cmd **cmd_to_lst(char **cmd, t_cmd **lst)
{
	int		i;
	t_cmd	*tmp;

	i = 0;
	tmp = NULL;
	while (cmd && cmd[i])
	{
		if (!(*lst))
		{
			(*lst) = nwlst(cmd, &i);
		}
		else
		{
			tmp = nwlst(cmd , &i);
		}
		if (tmp)
		{
			lst_add_back((lst), tmp);
		}
		tmp = NULL;
		// i++;
	}
	return (lst);
}


void print_lst(t_cmd *lst)
{
	int	i;

	i = 0;
	while (lst && lst->cmd)
	{
		printf("\nnext cmd :\n");
		if (lst->cmd)
		{
			printf("%s\n", lst->cmd[0]);
			// if (lst->cmd[1])
			// 	printf("%s\n", lst->cmd[1]);
		}
		// printf("redir : %p\n", lst->redir);
		// while (lst && lst->redir)
		// {
		// 	if (lst->redir->type)
		// 	{
		// 		printf("type : %d", lst->redir->type);
		// 		printf(" filename : %s\n", lst->redir->file_name);
		// 	}
		// 	if (lst->redir->redir_next)
		// 		lst->redir = lst->redir->redir_next;
		// 	else
		// 		break;
		// }
		if (lst->next)
			lst = lst->next;
		else
			break;
	}
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
