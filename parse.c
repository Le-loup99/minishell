/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakoto2 <arakoto2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 10:54:52 by arakoto2          #+#    #+#             */
/*   Updated: 2026/01/09 18:07:13 by arakoto2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <string.h>


char  **lst_env_to_tab(t_list *curr_env)
{
	int i = 0;
	char *temp = NULL;

	char **env = NULL;

	env = malloc(sizeof(char *) * (size_en(curr_env) + 1));
	while (curr_env)
	{
		if (curr_env->value)
		{
			temp = ft_strjoin(curr_env->name, "=");
			if (!curr_env->value[0])
				temp = ft_strjoin(temp, "\"\"");
		}
		else
			temp = curr_env->name;
		temp = ft_strjoin(temp, curr_env->value);
		env[i] = ft_strdup(temp);
		i++;
		curr_env = curr_env->next;
	}
	env[i] = NULL;
	return(env);
	
}

int      size_en(t_list *env)
{
	int len;

	len = 0;

	while (env)
	{
		len++;
		env = env->next;
	}
	return(len);
	
}
void	delete_file(t_cmd *lst)
{
	while (lst)
	{
		while(/*g_signal == SIGINT && */ lst->redir_in)
		{
			if (lst->redir_in && lst->redir_in->type == HEREDOC)
			{
				unlink(lst->redir_in->file_name);
			}
			lst->redir_in = lst->redir_in->redir_next;
		}
		lst = lst->next;
	}
}

int main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;
	t_cmd *lst;
	char **stock;
	char *str;
	char *path = NULL;
	int		check_hd;
	int fd[2];
	t_list  *curr_env;
	int fd_temp;
	pid_t pid = 0;
	curr_env = take_env(env);
	lst = NULL;
	check_hd = 0;
	fd_temp = 0;
	signal(SIGQUIT,  SIG_IGN);
	signal(SIGINT,  signal_handler);
	env_lst_add_back(&curr_env, lstnew("?", "0"));
	while ((str = readline("minishell$ ")))
	{
			add_history(str);
			env = lst_env_to_tab(curr_env);
			stock = cmd(str, curr_env);
			cmd_to_lst(stock , &lst);
			int size = ft_cmd_size(lst);
			check_hd = ft_heredoc(lst, curr_env, str);
			if (check_hd != -1)
			{
				if (g_signal != SIGINT && check_error_at_end(str) >= 0 && check_quote_error(str) >= 0 && check_operator_error(str) >= 0)
				{
					if(size == 1 && lst->is_builtin)
						ft_is_built_in(lst, &curr_env);
					else
						ft_execution(lst, env, fd_temp, path, fd, pid, size, curr_env);
				}
			}
			delete_file(lst);
			free(str);
			str = NULL;
			lst = NULL;
			signal(SIGQUIT,  SIG_IGN);
			signal(SIGINT,  signal_handler);
			if (g_signal == SIGINT)
			{
				ft_search_replace(&curr_env, "?", ft_itoa(130));
				int dev = open("/dev/tty", O_RDONLY);
				dup2(dev, 0);
				if(dev != 0)
					close(dev);
			}
			g_signal = SIGUSR1;
	}
	ft_putstr_fd("exit\n", 1);
	// return(ft_atoi(ft_return_env_value(curr_env, "?")));
	return (0);
}
