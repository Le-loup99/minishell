/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakoto2 <arakoto2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 19:37:53 by arakoto2          #+#    #+#             */
/*   Updated: 2025/12/23 09:49:42 by arakoto2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void create_heredoc_file(t_redir *heredoc)
{
	char	*line;
	int		fd;
	static int i = 0;
	char	*name;
	char	*tmp;

	name = ft_itoa(i);
	tmp = ft_strjoin("tmp",name);
	i++;
	fd = open (tmp , O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return ;
	line = NULL;
	while ((line = readline(">")))
	{
		if (!ft_strcmp(line, heredoc->file_name))
			break;
		ft_putendl_fd(line, fd);
	}
	heredoc->file_name = tmp;
	close (fd);
	return ;
}

int	ft_heredoc(t_cmd *lst)
{
	int	i;
	t_cmd	*tmp_lst;
	t_redir	*tmp_redir;

	i = 0;
	tmp_lst = lst;
	tmp_redir = NULL;
	if (!lst)
		return (0);
	while (tmp_lst)
	{
		tmp_redir = tmp_lst->redir;
		while (tmp_redir)
		{
			if (tmp_redir->type == HEREDOC)
				create_heredoc_file(tmp_redir);
			tmp_redir = tmp_redir->redir_next;
		}
		tmp_lst = tmp_lst->next;
	}
	return (0);
}
