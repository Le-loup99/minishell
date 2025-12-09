
#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <stdio.h>
# include <string.h> // aza adino ny manala azy

int		quote_checker(char *str);
char	*quote_clearer(char *str, char *cleared);
char	*converter(char *str, int *i);

typedef struct	s_cmd
{
 	char			*cmd;
 	struct s_cmd	*next;
}		t_cmd;

t_cmd   **cmd_to_lst(char **cmd, t_cmd **lst);
void    print_lst(t_cmd *lst);
int		ft_strchr(const char *s, int c);
int		ft_strlen(char *str);
int		calcul_env_size(char *str);
void	ft_strcat(char *dst, char *src);
char	*ft_strjoin(char *dst, char *src);
char	*ft_str_p_char(char *s1, char a);
void	free_pp(char **str);

# endif