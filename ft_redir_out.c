/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framanan <framanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 11:07:36 by framanan          #+#    #+#             */
/*   Updated: 2025/12/22 17:53:43 by framanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redir_out(t_cmd *lst, char *path, char **env, int fd_temp)
{

	while (lst->redir)
	{
		if (lst->redir->redir_next)
		{
			open(lst->redir->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			lst->redir = lst->redir->redir_next;
		}
		else
		{
			if(lst->redir->type == OUT)
			{

				lst->redir->fd = open(lst->redir->file_name, O_WRONLY | O_CREAT | O_TRUNC,
						0644);
			}
			else if(lst->redir->type == APPEND)
			{
				lst->redir->fd = open(lst->redir->file_name, O_WRONLY | O_CREAT | O_APPEND,
							0644);
			}
			if(fd_temp != 0)
				dup2(fd_temp, STDIN_FILENO);
			dup2(lst->redir->fd, STDOUT_FILENO);
			close(lst->redir->fd);
			execve(path, lst->cmd, env);
		}
	}
}
