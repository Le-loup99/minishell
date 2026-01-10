/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakoto2 <arakoto2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 13:21:40 by framanan          #+#    #+#             */
/*   Updated: 2026/01/10 08:41:57 by arakoto2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_path(char **env, char *cmd)
{
	char **path;
	char *curr_cmd = NULL;
	int i;

	i = 0;
	if (!cmd || !cmd[0])
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		return (cmd);
	}
	path = take_path(env);
	while (cmd && path && path[i])
	{
		curr_cmd = ft_strjoin(path[i], cmd);
		if (access(curr_cmd, X_OK) == 0)
			return (curr_cmd);
		i++;
	}
	return (NULL);
}