# プログラム名
NAME       := minishell
TREE_NAME  := tree_visualize

# ディレクトリ
PARSER_DIR  := ./parser
LEXER_DIR   := ./lexer
EXPANDER_DIR := ./expander
EXECUTER_DIR := ./executer
INCLUDE_DIRS := ./include

# コンパイラとフラグ
CC      := cc
CFLAGS  := -Wall -Wextra -Werror -g $(addprefix -I, $(INCLUDE_DIRS))

# ライブラリ
LIBFT_DIR := ./libft
LIBFT     := libft.a

# ソースファイル
SRCS := main.c \
        $(PARSER_DIR)/parse.c \
        $(LEXER_DIR)/token.c \
        $(PARSER_DIR)/parse_utils.c \
        $(LEXER_DIR)/token_utils.c \
        $(PARSER_DIR)/free.c

SRCS_TREE := tree_visualize.c \
             $(PARSER_DIR)/parse.c \
             $(LEXER_DIR)/token.c \
             $(PARSER_DIR)/parse_utils.c \
             $(LEXER_DIR)/token_utils.c \
             ./utils/free.c \
			 ./utils/print.c \
			 ./utils/init_minishell.c \
             $(EXPANDER_DIR)/env.c \
             $(PARSER_DIR)/parse_utils2.c \
             $(EXPANDER_DIR)/heredoc.c \
             $(EXPANDER_DIR)/get_next_line.c \
             $(EXPANDER_DIR)/delete_quote.c \
             $(EXECUTER_DIR)/executer.c \
             $(EXECUTER_DIR)/pid_list.c

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
