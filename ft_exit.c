/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framanan <framanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 14:49:39 by framanan          #+#    #+#             */
/*   Updated: 2026/01/08 11:02:44 by framanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char **str, t_list *curr_env)
{
	if (strcmp(str[0], "exit") == 0)
	{
		if (str[1] && ft_atoi(str[1]) > INT_MAX)
		{
			printf("bash: exit: a: numeric argument required\n");
			exit(2);
		}
		if (ft_count_line(str) == 1 || ft_atoi(str[1]) == 0)
			exit(0);
		else if (ft_count_line(str) == 2)
			exit(ft_atoi(str[1]));
	}
	if (strcmp(str[0], "exit") == 0 && ft_count_line(str) == 3)
	{
		if (ft_isalnum(ft_atoi(str[1])) == 0)
		{
			ft_putendl_fd("bash: exit: too many arguments", 2);
			ft_search_replace(&curr_env, "?", ft_itoa(1));
			return;
		}
	}
}
