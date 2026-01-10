/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framanan <framanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 08:20:11 by framanan          #+#    #+#             */
/*   Updated: 2025/12/26 15:18:20 by framanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*take_env(char **env)
{
	int i = 0;
	t_list *lst = NULL;
	char **temp;
	while (env[i])
	{
		temp = ft_split_env(env[i++]);
		env_lst_add_back(&lst, lstnew(temp[0], temp[1]));
	}
	return (lst);
}