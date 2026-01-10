/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakoto2 <arakoto2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 19:37:53 by arakoto2          #+#    #+#             */
/*   Updated: 2026/01/09 19:50:29 by arakoto2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_signal = SIGUSR1;

int	is_quote(char *str)
{
	int	i;

	i = 0;
	while(str && str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

void create_heredoc_file(t_redir *heredoc, t_list *env)
{
	char	*line;
	int		fd;
	static int i = 0;
	char	*name;
	char	*tmp;
	char	*result;
	char	*delimiter;
	// pid_t 	pid;

	fd = -1;
	while (fd < 0)
	{
		name = ft_itoa(i);
		tmp = ft_strjoin("tmp", name);
		free(name);
		i++;
		fd = open(tmp, O_CREAT | O_EXCL |O_WRONLY , 0644);
	}
	result = NULL;
	delimiter = malloc (ft_strlen(heredoc->file_name) + 1);
	if (!delimiter)
		return ;
	delimiter[0] = '\0';
	delimiter = filename_handler(heredoc->file_name, delimiter);
	// free(tmp);
	if (fd < 0)
		return ;
	line = NULL;
	signal(SIGINT, handler_hd);
	if (g_signal != SIGINT)
		(line = readline(">"));
	while (line && g_signal != SIGINT)
	{
		// pid = fork();
		// if(pid == 0)
		// {
			if (g_signal == SIGINT)
				break;
			result = malloc (ft_strlen(line) + 1);
			if (!result || g_signal == SIGINT)
				break;
			else
				result[0] = '\0';
			if (!ft_strcmp(line, delimiter) || g_signal == SIGINT)
				break;
			if (!is_quote(heredoc->file_name))
			{
				result = line_handler(&line, result, env);
				ft_putendl_fd(result, fd);
			}
			else
				ft_putendl_fd(line, fd);
			free(result);
			(line = readline(">"));
		// }
		// signal(SIGINT, SIG_IGN);
		
	}
	// pid = fork();
	// if (pid == 0)
	// {
		// line = readline(">");
		// if (!ft_strcmp(line, delimiter))
			// exit (0);
	// }
	heredoc->file_name = tmp;
	close (fd);
	return ;
}
// int	check_error(t_redir redir)
// {
		
// }

int	check_redir_error(t_redir *all_redir)
{
	t_redir	*tmp_redir;

	tmp_redir = all_redir;
	while (tmp_redir)
	{
		if (!tmp_redir->file_name)
		{
			ft_putendl_fd("syntax error", 2);
			return (-1);
		}
		tmp_redir = tmp_redir->redir_next;
	}
	return (0);
}

int	ft_heredoc(t_cmd *lst, t_list *env, char *str)
{
	t_cmd	*tmp_lst;
	t_redir	*tmp_redir;
	t_redir *tmp_all_redir;
	int		check;

	tmp_lst = lst;
	tmp_redir = NULL;
	check = -1;
	if (!lst)
		return (0);
	if (check_redir_error(lst->redir) >= 0 && check_error_at_end(str) >= 0 && check_quote_error(str) >= 0 && check_operator_error(str) >= 0)
		check = 0;
	while (tmp_lst)
	{
		tmp_redir = tmp_lst->redir_in;
		tmp_all_redir = tmp_lst->redir;
		while (tmp_redir)
		{
			while (tmp_all_redir && (tmp_all_redir->type != HEREDOC || tmp_all_redir->file_name == NULL))
			{
				if (tmp_all_redir && tmp_all_redir->file_name == NULL)
					return (-1);
				tmp_all_redir = tmp_all_redir->redir_next;
			}
			if (tmp_redir && tmp_redir->type == HEREDOC)
				create_heredoc_file(tmp_redir, env);
			if (tmp_redir)
				tmp_redir = tmp_redir->redir_next;
		}
		tmp_lst = tmp_lst->next;
	}
	return (check);
}
