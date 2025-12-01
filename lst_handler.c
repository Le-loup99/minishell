
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
	while(lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

void lst_add_back(t_cmd *lst, t_cmd *new)
{
	lst = lst_last(lst);
	lst->next = new;
	new->next = NULL;
}

void print_lst(t_cmd *lst)
{
	while (lst)
	{
		printf("%s\n", lst->cmd);
		lst = lst->next;
	}
}

t_cmd *cmd_to_lst(char **cmd, t_cmd *lst)
{
	int	i;

	i = 0;
	while (cmd && *cmd && **cmd)
	{
		if (i == 0)
		{
			lst = nwlst(cmd[i]);
		}
		else
		{
			lst_add_back(lst, nwlst(cmd[i]));
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
