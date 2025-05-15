
NAME       := minishell

PARSER_DIR  := ./parser
LEXER_DIR   := ./lexer
EXPANDER_DIR := ./expander
EXECUTER_DIR := ./executer
INCLUDE_DIRS := ./include
BUILT_IN_DIRS := ./built_in
UTILS_DIRS := ./utils

CC      := cc
CFLAGS  := -Wall -Wextra -Werror -g $(addprefix -I, $(INCLUDE_DIRS))

LIBFT_DIR := ./libft
LIBFT     := libft.a


SRCS		 := main.c \
             $(PARSER_DIR)/parser.c \
             $(PARSER_DIR)/parser_struct.c \
			 $(PARSER_DIR)/parser_utils.c \
             $(LEXER_DIR)/lexer.c \
             $(LEXER_DIR)/lexer_utils.c \
			 $(LEXER_DIR)/lexer_struct.c \
             $(EXPANDER_DIR)/expander.c \
             $(EXPANDER_DIR)/expander_utils.c \
			 $(EXPANDER_DIR)/expander_sub.c\
             $(EXPANDER_DIR)/heredoc.c \
             $(EXPANDER_DIR)/heredoc_readline.c \
             $(EXPANDER_DIR)/delete_quote.c \
             $(EXECUTER_DIR)/executer.c \
             $(EXECUTER_DIR)/executer_utils.c \
			 $(EXECUTER_DIR)/do_command.c\
             $(EXECUTER_DIR)/pid_list.c \
             $(EXECUTER_DIR)/fd_manage.c \
             $(UTILS_DIRS)/free1.c \
             $(UTILS_DIRS)/free2.c \
             $(UTILS_DIRS)/print1.c \
             $(UTILS_DIRS)/print2.c \
             $(UTILS_DIRS)/init_minishell.c \
             $(UTILS_DIRS)/signal.c \
             $(BUILT_IN_DIRS)/command_cd.c \
             $(BUILT_IN_DIRS)/command_echo.c \
             $(BUILT_IN_DIRS)/command_env.c \
             $(BUILT_IN_DIRS)/command_exit.c \
             $(BUILT_IN_DIRS)/command_export.c \
             $(BUILT_IN_DIRS)/command_export_utilis.c \
             $(BUILT_IN_DIRS)/command_pwd.c \
             $(BUILT_IN_DIRS)/command_unset.c \
             $(BUILT_IN_DIRS)/free.c \
             $(BUILT_IN_DIRS)/ft_setenv.c \
             $(BUILT_IN_DIRS)/parse_and_execute_builtin.c \
             $(BUILT_IN_DIRS)/utilis.c

OBJS      := $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L. -lft -lreadline

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)
	cp $(LIBFT_DIR)/$(LIBFT) .

clean:
	rm -f $(OBJS) $(OBJS_TREE)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME) $(TREE_NAME) $(LIBFT)

re: fclean all
