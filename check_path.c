/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framanan <framanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 13:21:40 by framanan          #+#    #+#             */
/*   Updated: 2025/12/22 15:42:18 by framanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_path(char **env, char *cmd)
{
	char **path;
	char *curr_cmd = NULL;
	int i;

	i = 0;
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