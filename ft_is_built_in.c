/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_built_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framanan <framanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 17:34:14 by framanan          #+#    #+#             */
/*   Updated: 2026/01/08 11:03:42 by framanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_built_in(t_cmd *lst, t_list **curr_env)
{
	if(strcmp(lst->cmd[0], "echo") == 0)
		ft_echo(lst);
	if (strcmp(lst->cmd[0], "unset") == 0)
		ft_unset(curr_env, lst->cmd);
	if (strcmp(lst->cmd[0], "export") == 0)
		ft_export(curr_env, lst);
	if (strcmp(lst->cmd[0], "env") == 0)
		print_env(*curr_env, lst);
	if (*lst->cmd && strcmp(lst->cmd[0], "cd") == 0)
		ft_cd(curr_env, lst->cmd);
	if (strcmp(lst->cmd[0], "exit") == 0)
		ft_exit(lst->cmd, *curr_env);
	if (*lst->cmd && strcmp(lst->cmd[0], "pwd") == 0)
		ft_pwd(lst);
	return(0);
}
