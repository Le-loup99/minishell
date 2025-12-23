/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framanan <framanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 22:49:58 by framanan          #+#    #+#             */
/*   Updated: 2025/12/22 18:05:56 by framanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_is_pipe(t_cmd *lst, int fd[2], char **env, int fd_temp, char *path)
{
	dup2(fd_temp, STDIN_FILENO);
	// close(fd_temp);
	close(fd[0]);
    if(lst->next)
    {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
    }
	execve(path, lst->cmd, env);
}