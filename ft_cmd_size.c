/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framanan <framanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 13:58:58 by framanan          #+#    #+#             */
/*   Updated: 2025/12/18 14:02:16 by framanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_cmd_size(t_cmd *cmd)
{
    int len;

    len = 0;

    while (cmd)
    {
        cmd = cmd->next;
        len++;
    }
    return(len);
}