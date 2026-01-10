/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakoto2 <arakoto2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 20:40:51 by framanan          #+#    #+#             */
/*   Updated: 2026/01/09 10:37:18 by arakoto2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execution(t_cmd *lst, char **env, int fd_temp, char *path, int fd[2], pid_t pid, int size, t_list *curr_env)
{
	int	exit_status;

	exit_status = 0;
	// printf("%s", lst->cmd[0]);
	while (lst)
	{
			path = check_path(env, lst->cmd[0]);
			pipe(fd);
			// if(/*path || */!lst->cmd[0])
				pid = fork();
			if (pid == 0)
			{
				signal (SIGQUIT, SIG_DFL);
				// if (!path && lst->cmd[0])
				// {
				// 	 exit (127);
				// }
				if(path || !lst->cmd[0])
				{
						if(lst && (lst->redir_in || lst->redir_out))
						{
							if(lst->redir_in)
								ft_redir_in(lst, path, env, fd, fd_temp, curr_env);
							if(lst->redir_out)
								ft_redir_out(lst, path, env, fd_temp, curr_env);
						}
						else
							ft_is_pipe(lst, fd, env, fd_temp, path, curr_env);
					
				}
				else
				{
					if(lst->cmd[0])
					{
						ft_putstr_fd("minishell: ", 2);
						ft_putstr_fd(lst->cmd[0], 2);
						ft_putstr_fd(": ", 2);
						ft_putstr_fd(" ", 2);
						ft_putendl_fd("command not found", 2);
						// ft_search_replace(&curr_env, "?", ft_itoa(127));
						// return (127);
						exit (127);
					}
				}
			}
			signal(SIGINT, SIG_IGN);
			signal(SIGQUIT, SIG_IGN);
			// if(fd_temp != 0)
			ft_dup_fd_temp(&fd, &fd_temp, size);
			lst = lst->next;
	}
	int status;
	close(fd[0]);
	close(fd[1]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		exit_status = WEXITSTATUS(status);
		// printf("%d", WEXITSTATUS(status));
		ft_search_replace(&curr_env, "?", ft_itoa(exit_status));
	}
	else if (WIFSIGNALED(status))
	{
		// printf("%d", WTERMSIG(status));
		exit_status = WTERMSIG(status);
		if (exit_status == SIGQUIT)
		{
			ft_putendl_fd("Quit (core dumped)", 2);
			ft_search_replace(&curr_env, "?", ft_itoa(131));
		}
		if (exit_status == 2)
		{
			ft_putchar_fd('\n', 1);
			ft_search_replace(&curr_env, "?", ft_itoa(130));
		}
		else if (exit_status == 11)
		{
			ft_putendl_fd("Segmentation fault (core dumped)", 2);
			ft_search_replace(&curr_env, "?", ft_itoa(139));
		}
	}
}
