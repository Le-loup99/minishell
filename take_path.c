/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framanan <framanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 10:21:35 by framanan          #+#    #+#             */
/*   Updated: 2025/12/17 18:55:35 by framanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **take_path(char **env)
{
    int i = 0;
    char *temp = NULL;
    char **path;
    while(env[i])
    {
        if(ft_strncmp(env[i], "PATH", 4) == 0)
        {
            temp = ft_substr(env[i],5, ft_strlen(env[i]));
            break;
        }
        i++;
    }
    path = ft_split(temp,':');
    free(temp);
    i = 0;
    while (path[i])
    {
        path[i] = ft_strjoin(path[i], "/");
        i++;
    }
    return(path);
}

