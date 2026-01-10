/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framanan <framanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 10:44:10 by framanan          #+#    #+#             */
/*   Updated: 2026/01/07 23:56:42 by framanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static int  check_new_line(char *str)
{
    int i;

    i = 0;
    if (!str || !str[i])
        return (0);
    if(str[i + 1] && str[i + 1] == 'n')
    {
        if(str && str[i] != '-')
            return(0);
    }
    i++;
    if (!str[i])
        return (0);
    while (str[i])
    {
        if (str[i] != 'n')
            return(0);
        i++;
    }
    return(1);
}

int check_new_line_tab(char **str)
{
    int i = 0;

    while (str[i])
    {
        if(check_new_line(str[i]))
            return(1);
        i++;
    }
    return(0);
}

void ft_echo(t_cmd *lst)
{
    char **str;
    int i;
    int fd = 0;

    i = 1;
    str = lst->cmd;
    while (check_new_line(str[i]))
            i++;
    while(str[i])
    {
        if(str[i])
        {
            if(lst->redir_out)
            {
                if (i == 1)
                    fd = take_fd(lst);
                else
                    fd = take_fd_append(lst);
                if(fd > 0)
                    ft_putstr_fd(str[i], fd);
            }
            else
                ft_putstr_fd(str[i], 1);
        }
        if(str[i] && str[i + 1])
        {
            if(lst->redir_out && lst->redir_out->fd)
            {
                if(fd > 0)
                    ft_putchar_fd(' ', fd);
            }
            else
                ft_putchar_fd(' ', 1);
        }
        if(str[i])
            i++;
    }
    if(!check_new_line_tab(str))
    {
        if(lst->redir_out && lst->redir_out->fd)
        {
            if(fd > 0)
                ft_putchar_fd('\n', fd);
        }
        else
            ft_putchar_fd('\n', 1);
    }
}
