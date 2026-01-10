/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_built_in.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framanan <framanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 10:20:21 by framanan          #+#    #+#             */
/*   Updated: 2026/01/07 14:42:19 by framanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	take_fd(t_cmd *lst)
{
    if(!lst->redir_out)
    {
        return(-1);
    }
	while (lst && lst->redir_out && lst->redir_out->redir_next)
	{
		if (open(lst->redir_out->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644) < 0)
		{
			ft_putstr_fd("minishell : ", 2);
			ft_putstr_fd(lst->redir_out->file_name, 2);
			ft_putendl_fd(" : permision diened", 2);
			return (-1);
		}
		lst->redir_out = lst->redir_out->redir_next;
	}
	lst->redir_out->fd = open(lst->redir_out->file_name,
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (lst->redir_out->fd < 0)
	{
		ft_putstr_fd("minishell : ", 2);
		ft_putstr_fd(lst->redir_out->file_name, 2);
		ft_putendl_fd(" : permision diened", 2);
		return (-1);
	}
	return (lst->redir_out->fd);
}

int	take_fd_append(t_cmd *lst)
{
    if(!lst->redir_out)
    {
        return(-1);
    }
	while (lst && lst->redir_out && lst->redir_out->redir_next)
	{
		if (open(lst->redir_out->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644) < 0)
		{
			ft_putstr_fd("minishell : ", 2);
			ft_putstr_fd(lst->redir_out->file_name, 2);
			ft_putendl_fd(" : permision diened", 2);
			return (-1);
		}
		lst->redir_out = lst->redir_out->redir_next;
	}
	lst->redir_out->fd = open(lst->redir_out->file_name,
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (lst->redir_out->fd < 0)
	{
		ft_putstr_fd("minishell : ", 2);
		ft_putstr_fd(lst->redir_out->file_name, 2);
		ft_putendl_fd(" : permision diened", 2);
		return (-1);
	}
	return (lst->redir_out->fd);
}