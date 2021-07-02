NAME = minishell

HEADER = includes/minishell.h

LIST = minishell.c init_env.c

LIST_UTILS = utils/ft_split.c utils/ft_strcmp.c utils/ft_putchar_fd.c utils/ft_putstr_fd.c \
	utils/ft_strncmp.c  utils/ft_strchr.c utils/ft_strjoin.c utils/ft_strlen.c utils/ft_strdup.c

LIST_CMD = commands/cmd_pwd.c commands/cmd_echo.c commands/cmd_env.c commands/cmd_export.c \
	commands/cmd_cd.c commands/cmd_unset.c commands/check_cmd.c commands/cmd_exit.c \

LIST_PIPE = pipe/pipex.c

FLAGS = 

OBJ = $(LIST:.c=.o)

OBJ_UTILS = $(LIST_UTILS:.c=.o)

OBJ_CMD = $(LIST_CMD:.c=.o)

OBJ_PIPE = $(LIST_PIPE:.c=.o)

.PHONY : all clean fclean re

all : $(NAME)

%.o : %.c $(HEADER)
	gcc $(FLAGS) -I $(HEADER) -c $< -o $@

${NAME} : $(OBJ) $(OBJ_CMD) $(OBJ_UTILS) $(OBJ_PIPE) $(HEADER)
	gcc $(FLAGS) $(OBJ) $(OBJ_CMD) $(OBJ_UTILS) $(OBJ_PIPE) -o $(NAME)

clean :
	$(RM) $(OBJ) $(OBJ_CMD) $(OBJ_UTILS) $(OBJ_PIPE)

fclean : clean
	$(RM) $(NAME)

re : fclean all