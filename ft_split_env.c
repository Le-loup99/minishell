/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framanan <framanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 14:50:50 by framanan          #+#    #+#             */
/*   Updated: 2026/01/07 16:31:01 by framanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **ft_split_env(char *str)
{
    int len;
    int temp;
    char **s;

    len = 0;
    if (str[1])
    {
        s = malloc(sizeof(char *) * 3);
        // if(ft_strchr(str, '=') == NULL)
        //     return(NULL);
        while(str[len] && str[len] != '=')
            len++;
        // if(str[len - 1] == ' ')
        //     return(NULL);
        s[0] = ft_substr(str, 0, len);
        len++;
        temp = len;
        while (str[len])
            len++;
        s[1] = ft_substr(str, temp, len);
        // printf("{%s}\n", s[0]);
        // printf("[%s]\n", s[1]);
        s[2] = NULL;
    }
    else
    {
        s = malloc(sizeof(char *) * 2);
        while(str[len] && str[len] != '=')
            len++;
        s[0] = ft_substr(str, 0, len);
        s[1] = NULL;
    }
    return(s);
}
