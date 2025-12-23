/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakoto2 <arakoto2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 17:46:09 by arakoto2          #+#    #+#             */
/*   Updated: 2025/12/22 17:48:30 by arakoto2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_arg(char **str)
{
    int i;

    i = 0;
    if (!str)
        return (0);
    if (*str)
        return (0);
    while(str[i])
        i++;
    return (i);
}
