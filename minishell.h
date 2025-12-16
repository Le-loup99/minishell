
#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <stdio.h>
# include <string.h> // aza adino ny manala azy

int		quote_checker(char *str);
char	*quote_clearer(char *str, char *cleared);
char	*converter(char *str, int *i);

typedef enum r_type
{
	IN,
	OUT,
	APPEND,
	HEREDOC,
	PIPE,
}	t_r_type;

typedef struct s_redir
{
	t_r_type			type;
	char				*file_name;
	int					fd;
	struct s_redir		*redir_next;
}		t_redir;

typedef struct	s_cmd
{
 	char			**cmd;
	// t_redir			*in;
	// t_redir			*out;
	t_redir			*redir;
	int				is_builtin;
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
int		check_error_at_end(char *str);
int		check_quote_error(char *str);
int		ft_strcmp(const char *s1, const char *s2);
int		check_operator_error(char *str);
int		check_after_redir(char **str);

# endif
