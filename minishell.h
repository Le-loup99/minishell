
#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"
# include <assert.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

int					quote_checker(char *str);
char				*quote_clearer(char **str, char *cleared, int *check_split_expand);
char				*converter(char *str, int *i);

typedef enum r_type
{
	IN,
	OUT,
	APPEND,
	HEREDOC,
}					t_r_type;

typedef struct s_redir
{
	t_r_type		type;
	char			*file_name;
	int				fd;
	struct s_redir	*redir_next;
}					t_redir;

typedef struct s_cmd
{
	char			**cmd;
	t_redir			*redir;
	int				is_builtin;
	struct s_cmd	*next;
}					t_cmd;

t_cmd				**cmd_to_lst(char **cmd, t_cmd **lst);
void				print_lst(t_cmd *lst);
int					calcul_env_size(char *str);
void				ft_strcat(char *dst, char *src);
char				*ft_strjoin_pars(char *dst, char *src);
char				*ft_str_p_char(char *s1, char a);
void				free_pp(char **str);
int					check_error_at_end(char *str);
int					check_quote_error(char *str);
int					ft_strcmp(const char *s1, const char *s2);
int					check_operator_error(char *str);
char				**take_path(char **env);
char				*check_path(char **env, char *cmd);
void				ft_execution(t_cmd *lst, char **env, int fd_temp,
						char *path, int fd[2], pid_t pid, int size);
int					ft_cmd_size(t_cmd *cmd);
void				ft_redir_out(t_cmd *lst, char *path, char **env,
						int fd_temp);
void				ft_redir_in(t_cmd *lst, char *path, char **env, int fd[2]);
void				ft_is_pipe(t_cmd *lst, int fd[2], char **env, int fd_temp,
						char *path);
void				ft_dup_fd_temp(int *fd[2], int *fd_temp, int size);
int					count_arg(char **str);
int					ft_heredoc(t_cmd *lst);

#endif
