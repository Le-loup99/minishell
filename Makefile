SRCS = check_error.c environment_variables.c free.c lst_handler.c \
       parse.c utils.c take_path.c check_path.c ft_execution.c ft_cmd_size.c \
	   ft_redir_out.c ft_redir_in.c ft_is_pipe.c ft_dup_temp.c lst_utils.c ft_heredoc.c \
	   ft_count_line.c ft_split_env.c take_env.c built_in.c \
       ft_search_replace.c ft_is_built_in.c lst.c ft_exit.c ft_echo.c ft_signal.c heredoc_helper.c \
	   ft_redir_built_in.c parse_algo.c expand.c parsing.c\

NAME = minishell

OBJECTS = $(SRCS:.c=.o)

LIBFT = ./libft/libft.a

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

all : $(NAME) $(LIBFT)

$(NAME) : $(OBJECTS)
		$(MAKE) -C ./libft
		$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT) -o $(NAME) -lreadline


clean :
		$(MAKE) -C ./libft clean
		rm -fr $(OBJECTS)

fclean : clean
		rm -fr $(NAME) $(LIBFT)

re : fclean all

.PHONY : all clean fclean re
