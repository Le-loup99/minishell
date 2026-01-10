/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_replace.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framanan <framanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 10:24:36 by framanan          #+#    #+#             */
/*   Updated: 2026/01/08 11:57:13 by framanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_if_cat(char *str)
{
	int	i;

	i = 0;
    if (!str)
    {
        return (0);
    }
	while (str[i] && str[i] != '=')
	{
		if (str[i] == '+')
			return (1);
		i++;
	}
	return (0);
}

void  ft_search_replace(t_list **lst, char *s1, char *s2)
{
    t_list *temp;
    int     check_cat;

    temp = *lst;
    check_cat = check_if_cat(s1);
    if (check_cat)
    {
        s1 = ft_substr(s1, 0, (ft_strlen(s1) - 1));
    }
    while(temp)
    {
        if(strcmp(temp->name, s1) == 0)
        {
            if (!check_cat && temp->value && s2)
            {
                // free(temp->value);
                temp->value = NULL;
            }
            if (s2)
            {
                if (check_cat)
                    temp->value = ft_strjoin(temp->value, s2);
                else
                    temp->value = ft_strdup(s2);
            }
                // if (temp->value)
            //     temp->name = ft_strjoin(temp->name, "=");
        }
        temp = temp->next;
    }
}