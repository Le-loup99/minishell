/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framanan <framanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 11:41:42 by framanan          #+#    #+#             */
/*   Updated: 2026/01/07 23:22:19 by framanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redir_in(t_cmd *lst, char *path, char **env, int fd[2],
		int fd_temp, t_list *curr_env)
{
	(void) fd_temp;
	(void) env;
	while (lst->redir_in)
	{
		if (lst->redir_in->redir_next)
		{
			lst->redir_in->fd = open(lst->redir_in->file_name, O_RDONLY);
			if (lst->redir_in->fd < 0)
			{
				printf("bash: %s: No such file or directory\n",
					lst->redir_in->file_name);
				exit(1);
			}
			dup2(lst->redir_in->fd, STDIN_FILENO);
			close(lst->redir_in->fd);
			if (lst->redir_in->type == HEREDOC)
				unlink(lst->redir_in->file_name);
			lst->redir_in = lst->redir_in->redir_next;
		}
		else
		{
			lst->redir_in->fd = open(lst->redir_in->file_name, O_RDONLY);
			if (lst->redir_in->fd < 0)
			{
				printf("bash: %s: No such file or directory\n",
					lst->redir_in->file_name);
				// ft_search_replace(&curr_env, "?", "1");
				exit(1);
			}
			dup2(lst->redir_in->fd, STDIN_FILENO);
			close(lst->redir_in->fd);
			if (lst->redir_in->type == HEREDOC)
				unlink(lst->redir_in->file_name);
			if(lst->redir_out)
				return;
			if (lst->next)
				dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
			if (lst->is_builtin)
				ft_is_built_in(lst, &curr_env);
			else
				execve(path, lst->cmd, NULL);
			exit(127);
		}
	}
}
