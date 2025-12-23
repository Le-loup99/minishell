/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup_temp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framanan <framanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 11:41:41 by framanan          #+#    #+#             */
/*   Updated: 2025/12/20 11:54:45 by framanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_dup_fd_temp(int *fd[2], int *fd_temp, int size)
{
	if (*fd_temp != 0)
		close(*fd_temp);
	if (size > 1)
		*fd_temp = dup(fd[0][0]);
	close(fd[0][0]);
	close(fd[0][1]);
}