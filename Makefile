SRCS = check_error.c environment_variables.c free.c lst_handler.c \
       parse.c utils.c take_path.c check_path.c ft_execution.c ft_cmd_size.c \
	   ft_redir_out.c ft_redir_in.c ft_is_pipe.c ft_dup_temp.c lst_utils.c ft_heredoc.c \

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
