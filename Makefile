NAME = minishell

HEADER = includes/minishell.h

LIST = minishell.c init_env.c work_with_fd.c

LIST_UTILS = utils/ft_split.c utils/ft_strcmp.c utils/ft_putchar_fd.c utils/ft_putstr_fd.c \
	utils/ft_strncmp.c  utils/ft_strchr.c utils/ft_strjoin.c utils/ft_strlen.c utils/ft_strdup.c \
	utils/ft_putnbr_fd.c utils/ft_substr.c

LIST_CMD = commands/cmd_pwd.c commands/cmd_echo.c commands/cmd_env.c commands/cmd_export.c \
	commands/cmd_cd.c commands/cmd_unset.c commands/other_cmd.c commands/cmd_exit.c 

LIST_PARSER = parser/preparser.c

LIST_PIPE = pipe/pipex.c

LIST_SIGNAL = signal/signal_init.c

READLINE =  -L/Users/$(USER)/.brew/Cellar/readline/8.1/lib/ -lreadline

FLAGS = 

OBJ = $(LIST:.c=.o)

OBJ_UTILS = $(LIST_UTILS:.c=.o)

OBJ_CMD = $(LIST_CMD:.c=.o)

OBJ_PARSER = $(LIST_PARSER:.c=.o)

OBJ_PIPE = $(LIST_PIPE:.c=.o)

OBJ_LIST_SIGNAL = $(LIST_SIGNAL:.c=.o)

.PHONY : all clean fclean re

all : $(NAME)

%.o : %.c $(HEADER)
	gcc $(FLAGS) -I $(HEADER) -c $< -o $@

${NAME} : $(OBJ) $(OBJ_CMD) $(OBJ_PARSER) $(OBJ_UTILS) $(OBJ_PIPE) $(OBJ_LIST_SIGNAL) $(HEADER)
	gcc $(READLINE) $(FLAGS) $(OBJ) $(OBJ_CMD) $(OBJ_PARSER) $(OBJ_UTILS) $(OBJ_PIPE) $(OBJ_LIST_SIGNAL) -o $(NAME)

clean :
	$(RM) $(OBJ) $(OBJ_CMD) $(OBJ_PARSER) $(OBJ_UTILS) $(OBJ_PIPE) $(OBJ_LIST_SIGNAL)

fclean : clean
	$(RM) $(NAME)

re : fclean all