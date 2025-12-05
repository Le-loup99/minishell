
#include "minishell.h"

t_cmd *nwlst(char *cmd)
{
	t_cmd	*new;

	new = malloc (sizeof(t_cmd));
	new->cmd = cmd;
	new->next = NULL;
	return (new);
}

t_cmd *lst_last(t_cmd *lst)
{
	while(lst && lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

void lst_add_back(t_cmd *lst, t_cmd *new)
{
	lst = lst_last(lst);
	if (!new)
		return ;
	lst->next = new;
	new->next = NULL;
}

void print_lst(t_cmd *lst)
{
	while (lst && lst->cmd)
	{
		if (lst->cmd)
			printf("%s\n", lst->cmd);
		if (lst->next)
			lst = lst->next;
		else
			break;
	}
}

t_cmd **cmd_to_lst(char **cmd, t_cmd **lst)
{
	int		i;
	t_cmd	*tmp;

	i = 0;
	tmp = NULL;
	while (cmd && cmd[i])
	{
		if (i == 0)
		{
			(*lst) = nwlst(cmd[i]);
		}
		else
		{
			tmp = nwlst(cmd[i]);
		}
		if (tmp)
		{
			lst_add_back((*lst), tmp);
		}
		i++;
	}
	return (lst);
}

// int main()
// {
// 	t_cmd *head;
// 	t_cmd *second;
// 	t_cmd *third;

// 	head = nwlst("test");
// 	second = nwlst("is it");
// 	third = nwlst("troisgedy");
// 	lst_add_back(head, second);
// 	lst_add_back(head, NULL);
// 	lst_add_back(head, nwlst("troitroi"));
// 	print_lst(head);	
// }
