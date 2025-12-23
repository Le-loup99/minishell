/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framanan <framanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 11:41:42 by framanan          #+#    #+#             */
/*   Updated: 2025/12/22 17:59:19 by framanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redir_in(t_cmd *lst,char *path, char **env, int fd[2])
{
	while(lst->redir->redir_next)
	{
		lst->redir = lst->redir->redir_next;
	}
	lst->redir->fd = open(lst->redir->file_name, O_RDONLY);
	dup2(lst->redir->fd, STDIN_FILENO);
	close(lst->redir->fd);
    if(lst->next)
	{
		close(fd[0]);
	    dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	execve(path, lst->cmd, env);
}