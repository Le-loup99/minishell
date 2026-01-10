/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framanan <framanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 22:49:58 by framanan          #+#    #+#             */
/*   Updated: 2026/01/08 10:41:28 by framanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_is_pipe(t_cmd *lst, int fd[2], char **env, int fd_temp, char *path, t_list *curr_env)
{
    (void) env;
    struct stat st;
    stat(path, &st);
    if (S_ISDIR(st.st_mode))
    {
        ft_putstr_fd("minishell : ", 2);
        ft_putstr_fd(path, 2);
        ft_putendl_fd(" : Is a directory", 2);
        exit(1);
    }
    if(fd_temp != 0)
	    dup2(fd_temp, STDIN_FILENO);
	// close(fd_temp);
	close(fd[0]);
    if(lst->next)
    {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
    }
    if(lst->is_builtin)
        ft_is_built_in(lst,&curr_env);
    else
	    execve(path, lst->cmd, env);
    exit(127);
}
