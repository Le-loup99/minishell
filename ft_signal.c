/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framanan <framanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 09:09:49 by framanan          #+#    #+#             */
/*   Updated: 2026/01/06 10:44:39 by framanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
void	handler_hd(int signum)
{
	// int fd;
	g_signal = signum;
	// fd = dup(0);
	// close(0);
	// dup2(0, fd);
    write(1, "\n", 1);
	close(0);
	// rl_done = 1;
    // rl_replace_line("", 0);
	// rl_eof_found = 1;
}
