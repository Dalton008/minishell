NAME = minishell

HEADER = includes/minishell.h

LIST = minishell.c for_main.c

LIST_UTILS = $(shell find ./utils -name "*.c")

LIST_CMD = $(shell find ./commands -name "*.c")

LIST_PARSER = $(shell find ./parser -name "*.c")

LIST_PIPE = $(shell find ./pipe -name "*.c")

LIST_SIGNAL = $(shell find ./signal -name "*.c")

LIST_PREPARSER = $(shell find ./preparser -name "*.c")

READLINE =  -L/Users/$(USER)/.brew/Cellar/readline/8.1/lib/ -lreadline

FLAGS = -Wall -Wextra -Werror

OBJ = $(LIST:.c=.o)

OBJ_UTILS = $(LIST_UTILS:.c=.o)

OBJ_CMD = $(LIST_CMD:.c=.o)

OBJ_PARSER = $(LIST_PARSER:.c=.o)

OBJ_PIPE = $(LIST_PIPE:.c=.o)

OBJ_LIST_SIGNAL = $(LIST_SIGNAL:.c=.o)

OBJ_PREPARSER = $(LIST_PREPARSER:.c=.o)

.PHONY : all clean fclean re

all : $(NAME)

%.o : %.c $(HEADER)
	gcc -g $(FLAGS) -I $(HEADER) -c $< -o $@

${NAME} : $(OBJ) $(OBJ_CMD) $(OBJ_PARSER) $(OBJ_UTILS) $(OBJ_PIPE) $(OBJ_LIST_SIGNAL) $(OBJ_PREPARSER) $(HEADER)
	gcc $(READLINE) $(FLAGS) $(OBJ) $(OBJ_CMD) $(OBJ_PARSER) $(OBJ_UTILS) $(OBJ_PIPE) $(OBJ_LIST_SIGNAL) $(OBJ_PREPARSER) -o $(NAME)

clean :
	$(RM) $(OBJ) $(OBJ_CMD) $(OBJ_PARSER) $(OBJ_UTILS) $(OBJ_PIPE) $(OBJ_LIST_SIGNAL) $(OBJ_PREPARSER)

fclean : clean
	$(RM) $(NAME)

re : fclean all