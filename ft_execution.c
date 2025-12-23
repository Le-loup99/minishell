/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakoto2 <arakoto2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 20:40:51 by framanan          #+#    #+#             */
/*   Updated: 2025/12/23 09:37:45 by arakoto2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execution(t_cmd *lst, char **env, int fd_temp, char *path, int fd[2], pid_t pid, int size)
{
	while (lst)
	{
		path = check_path(env, lst->cmd[0]);
		// if (path)
		// {
			pipe(fd);
			pid = fork();
			if (pid == 0)
			{
				if(path)
				{
					if (lst && lst->next)
					{
						if(lst && lst->redir)
						{
							if(lst->redir->type == HEREDOC)
							{
								lst->redir->fd = open(lst->redir->file_name, O_RDONLY , 0644);
								dup2(lst->redir->fd, STDIN_FILENO);
								if(lst->next)
								{
									dup2(fd[1], STDOUT_FILENO);
								}
								execve(path, lst->cmd, env);
							}
							else if(lst->redir->type == OUT || lst->redir->type == APPEND)
								ft_redir_out(lst, path, env, fd_temp);
							else if(lst->redir->type == IN)
								ft_redir_in(lst, path, env, fd);
						}
						else
							ft_is_pipe(lst, fd, env, fd_temp, path);
					}
					else
					{
						if(lst && lst->redir)
						{
							if(lst->redir->type == HEREDOC)
							{
								lst->redir->fd = open(lst->redir->file_name, O_RDONLY , 0644);
								dup2(lst->redir->fd, STDIN_FILENO);
								execve(path, lst->cmd, env);
							}
							if(lst->redir->type == OUT || lst->redir->type == APPEND)
								ft_redir_out(lst, path, env, fd_temp);
							else if(lst->redir->type == IN)
								ft_redir_in(lst, path, env, fd);
						}
						else
							ft_is_pipe(lst, fd, env, fd_temp, path);
					}
				}
				else
				{
					if(lst->cmd[0])
						printf("%s command not found\n", lst->cmd[0]);
				}

			}
		// }
		// else
		// {
		// 	printf("%s command not found\n", lst->cmd[0]);
		// 	break;
		// }
		ft_dup_fd_temp(&fd, &fd_temp, size);
		lst = lst->next;
	}
	int status;
	close(fd[0]);
	close(fd[1]);
	waitpid(pid, &status, 0);
}
