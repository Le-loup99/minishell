/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakoto2 <arakoto2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 11:07:36 by framanan          #+#    #+#             */
/*   Updated: 2026/01/09 09:28:00 by arakoto2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redir_out(t_cmd *lst, char *path, char **env, int fd_temp, t_list *curr_env)
{
	(void)fd_temp;
	(void) env;
	while (lst->redir_out)
	{
		if (lst->redir_out->redir_next)
		{
			if(open(lst->redir_out->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644) < 0)
			{
				ft_putstr_fd("minishell : ", 2);
				ft_putstr_fd(lst->redir_out->file_name, 2);
				ft_putendl_fd(" : Permision denied", 2);
				return;
			}
			lst->redir_out = lst->redir_out->redir_next;
		}
		else
		{
			if(lst->redir_out->type == OUT)
			{
				lst->redir_out->fd = open(lst->redir_out->file_name, O_WRONLY | O_CREAT | O_TRUNC,
						0644);
			}
			if(lst->redir_out->type == APPEND)
			{
				lst->redir_out->fd = open(lst->redir_out->file_name, O_WRONLY | O_CREAT | O_TRUNC,
						0644);
			}
			if(lst->redir_out->fd < 0)
			{
				ft_putstr_fd("minishell : ", 2);
				ft_putstr_fd(lst->redir_out->file_name, 2);
				ft_putendl_fd(" : Permision denied", 2);
				return;
			}
			// if(fd_temp != 0)
			// 	dup2(fd_temp, STDIN_FILENO);
			dup2(lst->redir_out->fd, STDOUT_FILENO);
			close(lst->redir_out->fd);
			if(lst->is_builtin)
				ft_is_built_in(lst, &curr_env);
			else
				execve(path, lst->cmd, env);
			exit(127);
		}
	}
}
