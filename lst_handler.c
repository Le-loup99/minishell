/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakoto2 <arakoto2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 12:36:00 by arakoto2          #+#    #+#             */
/*   Updated: 2026/01/09 21:50:15 by arakoto2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir(char *str)
{
	if (!ft_strcmp(str, "<") || !ft_strcmp(str, "<<"))
		return (1);
	else if (!ft_strcmp(str, ">") || !ft_strcmp(str, ">>"))
		return (2);
	return (0);
}

int	check_redir(char **argv, int i)
{
	int	j;

	j = i;
	while (argv && argv[j])
	{
		if (!ft_strcmp(argv[j], "<") || !ft_strcmp(argv[j], "<<")
			|| !ft_strcmp(argv[j], ">") || !ft_strcmp(argv[j], ">>"))
			return (1);
		j++;
	}
	return (0);
}

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
	if (!is_redir(target))
		new_redir->file_name = target;
	else
		new_redir->file_name = NULL;
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
// t_redir	*implement_redir_helper(char **argv, int *i)
// {
// 	t_redir	*final;
// 	t_redir *tmp;

// 	final = NULL;
// 	tmp = NULL;
// 	if (!final)
// 	{
// 		final = new_redir(argv[(*i)], argv[(*i) + 1]);
// 		(*i)++;
// 	}
// 	else
// 	{
// 		tmp = new_redir(argv[(*i)], argv[(*i) + 1]);
// 		(*i)++;
// 	}
// 	if (tmp)
// 		redir_add_back(final, tmp);
// 	(*i)++;
// 	tmp = NULL;
// 	return (final);
// }

t_redir	*implement_redir_in(char **argv, int *i)
{
	t_redir	*final;
	t_redir *tmp;

	final = NULL;
	tmp = NULL;
	while (argv[(*i)] && ft_strcmp(argv[(*i)], "|"))
	{
		if (!ft_strcmp(argv[(*i)], "|"))
			break;
		if (is_redir(argv[(*i)]) == 1)
		{
			// implement_redir_helper(argv, i, &final);
			if (!final)
			{
				final = new_redir(argv[(*i)], argv[(*i) + 1]);
				if (argv[(*i) + 1] && !final->file_name)
					(*i)--;
				(*i)++;
			}
			else
			{
				tmp = new_redir(argv[(*i)], argv[(*i) + 1]);
				if (argv[(*i) + 1] && !tmp->file_name)
					(*i)--;
				(*i)++;
			}
			if (tmp)
				redir_add_back(final, tmp);
			(*i)++;
			tmp = NULL;
		}
		else if (is_redir(argv[(*i)]) == 2)
		{
			if (!argv[(*i) + 1] || is_redir(argv[(*i) + 1]))
				(*i) += 1;
			else
				(*i) += 2;
		}
		else if (!check_redir(argv, (*i)))
			break ;
		else
			(*i)++;
	}
	return (final);
}

t_redir	*implement_redir_out(char **argv, int *i)
{
	t_redir	*final;
	t_redir *tmp;

	final = NULL;
	tmp = NULL;
	while (argv[(*i)] && ft_strcmp(argv[(*i)], "|"))
	{
		if (!ft_strcmp(argv[(*i)], "|"))
			break;
		if (is_redir(argv[(*i)]) == 2)
		{
			if (!final)
			{
				final = new_redir(argv[(*i)], argv[(*i) + 1]);
				if (argv[(*i) + 1] && !final->file_name)
					(*i)--;
				(*i)++;
			}
			else
			{
				tmp = new_redir(argv[(*i)], argv[(*i) + 1]);
				if (argv[(*i) + 1] && !tmp->file_name)
					(*i)--;
				(*i)++;
			}
			if (tmp)
				redir_add_back(final, tmp);
			(*i)++;
			tmp = NULL;
		}
		else if (is_redir(argv[(*i)]) == 1)
		{
			if (!argv[(*i) + 1] || is_redir(argv[(*i) + 1]))
				(*i) += 1;
			else
				(*i) += 2;
		}
		else if (!check_redir(argv, (*i)))
			break ;
		else
			(*i)++;
	}
	return (final);
}

t_redir	*implement_redir(char **argv, int *i)
{
	t_redir	*final;
	t_redir *tmp;

	final = NULL;
	tmp = NULL;
	while (argv[(*i)] && ft_strcmp(argv[(*i)], "|"))
	{
		if (!ft_strcmp(argv[(*i)], "|"))
			break;
		if (is_redir(argv[(*i)]))
		{
			if (!final)
			{
				final = new_redir(argv[(*i)], argv[(*i) + 1]);
				if (argv[(*i) + 1] && !final->file_name)
					(*i)--;
				(*i)++;
			}
			else
			{
				tmp = new_redir(argv[(*i)], argv[(*i) + 1]);
				if (argv[(*i) + 1] && !tmp->file_name)
					(*i)--;
				(*i)++;
			}
			if (tmp)
				redir_add_back(final, tmp);
			(*i)++;
			tmp = NULL;
		}
		else if (!check_redir(argv, (*i)))
			break ;
		else
			(*i)++;
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

char	*clear_pipe(char **str)
{
	int		check;
	int		i;
	char	*final;
	int		j;

	check = 0;
	i = 0;
	j = 0;
	if (!*str)
		return (NULL);
	final = malloc(ft_strlen(*str) + 1);
	while ((*str)[i])
	{
		if ((*str)[i] != '|')
			check = 0;
		final[j] = (*str)[i];
		if ((*str)[i] == '|' && check == 0)
		{
			check = 1;
			i += 1;
		}
		else
		{
			i++;
			j++;
		}
	}
	free (*str);
	return (final);
}

t_cmd *nwlst(char **argv, int *i)
{
	t_cmd	*new;
	char	*special;
	int		cmd_index;
	int		tmp;

	cmd_index = 0;
	special = NULL;
	new = malloc (sizeof(t_cmd));
	new->cmd = malloc (sizeof(char *) * (count_arg(argv) + 2));
	new->is_builtin = 0;
	new->redir_in = NULL;
	new->redir_out = 0;
	new->cmd[0] = NULL;
	tmp = *i;
	new->redir_in = implement_redir_in(argv, &tmp);
	tmp = *i;
	new->redir = implement_redir(argv, &tmp);
	tmp = *i;
	new->redir_out = implement_redir_out(argv, &tmp);
	// new->in = NULL;
	// new->out = NULL;
	while (argv && argv[(*i)])
	{
		if (!ft_strcmp(argv[(*i)], "<") || !ft_strcmp(argv[(*i)] , "<<")
			|| !ft_strcmp(argv[(*i)], ">") || !ft_strcmp(argv[(*i)] , ">>"))
		{
			(*i) += 2;
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
			if (check_count_pipe(argv[(*i)]))
				argv[(*i)] = clear_pipe(&(argv[(*i)]));
				// argv[(*i)] = ft_substr(argv[(*i)], 0, (ft_strlen(argv[(*i)]) - 1));
			if (new->is_builtin != 1)
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


// void print_lst(t_cmd *lst)
// {
// 	// int	i;
// 	t_redir	*tmp;

// 	tmp = NULL;
// 	if (!lst)
// 		return ;
// 	if (lst->redir)
// 		tmp = (lst->redir);
// 	// i = 0;
// 	while (lst && lst->cmd)
// 	{
// 		printf("\nnext cmd :\n");
// 		if (lst->cmd)
// 		{
// 			printf("%s\n", lst->cmd[0]);
// 			if (lst->cmd && lst->cmd[0] && lst->cmd[1])
// 				printf("%s\n", lst->cmd[1]);
// 		}
// 		while (tmp)
// 		{
// 			if (tmp)
// 			{
// 				printf("type : %d", tmp->type);
// 				printf(" filename : %s\n", tmp->file_name);
// 			}
// 			if (tmp->redir_next)
// 				tmp = tmp->redir_next;
// 			else
// 				break;
// 		}
// 		if (lst->next)
// 			lst = lst->next;
// 		else
// 			break;
// 	}
// }
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
