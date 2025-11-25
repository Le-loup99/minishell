
#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <stdio.h>
# include <string.h> // aza adino ny manala azy

int		quote_checker(char *str);
char	*quote_clearer(char *str, char *cleared);
char	*converter(char *str, int *i);

// typedef struct	s_cmd
// {
// 	char			*cmd;
// 	struct s_cmd	*next;
// }		t_cmd;

# endif