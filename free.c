/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakoto2 <arakoto2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 11:55:39 by arakoto2          #+#    #+#             */
/*   Updated: 2026/01/07 14:22:52 by arakoto2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_pp(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		free(str[i]);
		i++;
	}
	// if (*str)
	//     free(*str);
}

void	free_redir_lst(t_cmd *tmp)
{
	t_redir	*tmp_redir;

	while (tmp->redir_in)
	{
		tmp_redir = tmp->redir_in;
		tmp->redir_in = tmp->redir_in->redir_next;
		free(tmp_redir);
	}
	while (tmp->redir_out)
	{
		tmp_redir = tmp->redir_out;
		tmp->redir_out = tmp->redir_out->redir_next;
		free(tmp_redir);
	}
	return ;
}

void	free_cmd(t_cmd **cmd)
{
	t_cmd	*tmp;
	t_redir	*tmp_redir;
	int i;

	tmp_redir = NULL;
	tmp = *cmd;
	i = 0;
	while (*cmd)
	{
		(*cmd) = (*cmd)->next;
		while (tmp->cmd[i])
		{
			free(tmp->cmd[i]);
			i++;
		}
		free_redir_lst(tmp);
		free(tmp);
		tmp = (*cmd);
	}
	free(*cmd);
	return ;
}
