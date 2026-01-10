
#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"
# include "signal.h"
# include <assert.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <unistd.h>
extern int g_signal;

int					quote_checker(char *str);

typedef enum e_type
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
	t_redir			*redir_in;
	t_redir			*redir_out;
	t_redir			*redir;
	int				is_builtin;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_list
{
	char			*name;
	char			*value;
	struct s_list	*next;
}					t_list;

char **cmd(char *str, t_list *env);
char				*quote_clearer(char **str, char *cleared, int	*check_split_expand, int not_first, t_list *env);
char				*converter(char *str, int *i, t_list *env);
t_cmd				**cmd_to_lst(char **cmd, t_cmd **lst);
// void				print_lst(t_cmd *lst);
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
						char *path, int fd[2], pid_t pid, int size,
						t_list *curr_env);
int					ft_cmd_size(t_cmd *cmd);
void				ft_redir_out(t_cmd *lst, char *path, char **env,
						int fd_temp, t_list *curr_env);
void				ft_redir_in(t_cmd *lst, char *path, char **env, int fd[2],
						int fd_temp, t_list *curr_env);
void				ft_is_pipe(t_cmd *lst, int fd[2], char **env, int fd_temp,
						char *path, t_list *curr_env);
void				ft_dup_fd_temp(int *fd[2], int *fd_temp, int size);
int					count_arg(char **str);
int					ft_heredoc(t_cmd *lst, t_list *env, char *str);

int					ft_count_line(char **str);
char				**ft_split_env(char *str);
t_list				*take_env(char **env);
t_list				*lstnew(char *name, char *value);
void				env_lst_add_back(t_list **lst, t_list *new);
void				ft_export(t_list **lst, t_cmd *list);
void				print_env(t_list *curr_env, t_cmd *lst);
void				ft_search_replace(t_list **lst, char *s1, char *s2);
void				lst_remove(t_list **lst, char *str);
void				ft_unset(t_list **lst, char **str);
void				ft_cd(t_list **lst, char **str);
void				ft_pwd(t_cmd *lst);
int					ft_is_built_in(t_cmd *lst, t_list **curr_env);
char				*ft_return_env_value(t_list *lst, char *name);
void				ft_exit(char **str, t_list *curr_env);
void				ft_echo(t_cmd *lst);
void				signal_handler(int signum);
char				*filename_handler(char *str, char *cleared);
char				*line_handler(char **str, char *cleared, t_list *env);
int                 size_en(t_list *env);
char  **lst_env_to_tab(t_list *curr_env);
char   **sort_tab(char **str);
void  ft_prin_tab(char **str, int fd);
void    handler_hd(int signum);
int		take_fd(t_cmd *lst);
int		take_fd_append(t_cmd *lst);
int		check_if_cat(char *str);
int		count_cmd(char *str);
char 	**tokenisation(char *str);
char	*expand(char **str, char *cleared, int not_first, t_list *env);
char	**expand_all(char **all_cmd, char **cleared, t_list *env);
int		check_count_pipe(char *str);

#endif
