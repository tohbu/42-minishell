# プログラム名
NAME       := minishell
TREE_NAME  := tree_visualize

# ディレクトリ
PARSER_DIR  := ./parser
LEXER_DIR   := ./lexer
EXPANDER_DIR := ./expander
EXECUTER_DIR := ./executer
INCLUDE_DIRS := ./include
BUILT_IN_DIRS := ./built_in
UTILS_DIRS := ./utils

# コンパイラとフラグ
CC      := cc
CFLAGS  := -Wall -Wextra -Werror -g $(addprefix -I, $(INCLUDE_DIRS))

# ライブラリ
LIBFT_DIR := ./libft
LIBFT     := libft.a

# ソースファイル
SRCS := main.c \
        $(PARSER_DIR)/parser.c \
        $(LEXER_DIR)/token.c \
        $(PARSER_DIR)/parse_utils.c \
        $(LEXER_DIR)/token_utils.c \
        $(PARSER_DIR)/free.c

SRCS_TREE := tree_visualize.c \
             $(PARSER_DIR)/parser.c \
             $(PARSER_DIR)/parser_struct.c \
			 $(PARSER_DIR)/parser_utils.c \
             $(LEXER_DIR)/lexer.c \
             $(LEXER_DIR)/lexer_utils.c \
             $(EXPANDER_DIR)/expander.c \
             $(EXPANDER_DIR)/expander_utils.c \
			 $(EXPANDER_DIR)/expand_last_state.c\
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

# オブジェクトファイル
OBJS      := $(SRCS:.c=.o)
OBJS_TREE := $(SRCS_TREE:.c=.o)

# デフォルトターゲット
all: $(NAME)

# minishell のビルド
$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L. -lft -lreadline

# libft のビルド
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)
	cp $(LIBFT_DIR)/$(LIBFT) .

# tree_visualize のビルド
tree: $(OBJS_TREE) $(LIBFT)
	$(CC) $(CFLAGS) -o $(TREE_NAME) $(OBJS_TREE) -L. -lft -lreadline

# クリーン
clean:
	rm -f $(OBJS) $(OBJS_TREE)
	$(MAKE) clean -C $(LIBFT_DIR)

# フルクリーン
fclean: clean
	rm -f $(NAME) $(TREE_NAME) $(LIBFT)

# 再ビルド
re: fclean all
