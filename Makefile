# プログラム名
NAME = minishell
TREE_NAME = tree_visualize  # tree_visualizeの実行ファイル名

# ディレクトリの定義
PARSER_DIR = ./parser
LEXER_DIR = ./lexer
INCLUDE_DIRS = $(PARSER_DIR) $(LEXER_DIR) ./expander# ヘッダーファイルディレクトリ

# ソースファイル
SRCS = main.c $(PARSER_DIR)/parse.c $(LEXER_DIR)/token.c $(PARSER_DIR)/parse_utils.c $(LEXER_DIR)/token_utils.c $(PARSER_DIR)/free.c
SRCS_TREE = tree_visualize.c $(PARSER_DIR)/parse.c $(LEXER_DIR)/token.c $(PARSER_DIR)/parse_utils.c $(LEXER_DIR)/token_utils.c $(PARSER_DIR)/free.c ./expander/env.c $(PARSER_DIR)/parse_utils2.c

# オブジェクトファイル)?
OBJS = $(SRCS:.c=.o)
OBJS_TREE = $(SRCS_TREE:.c=.o)

# コンパイラとフラグ
CC = cc
CFLAGS = -Wall -Wextra -Werror -g $(addprefix -I, $(INCLUDE_DIRS))  # ヘッダーファイルディレクトリを追加

# ライブラリの指定
LIBFT = libft.a

# ルール
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L. -lft

$(LIBFT):
	make -C ./libft
	cp ./libft/libft.a .

clean:
	rm -f $(OBJS)
	rm -f $(OBJS_TREE)
	make clean -C ./libft

fclean: clean
	rm -f $(NAME)
	rm -f $(TREE_NAME)  # tree_visualize の実行ファイルも削除
	make fclean -C ./libft
	rm libft.a

re: fclean all

# treeのターゲット：tree_visualize用の実行ファイルを作成
tree: $(OBJS_TREE) $(LIBFT)
	$(CC) $(CFLAGS) -o $(TREE_NAME) $(OBJS_TREE) -L. -lft  # tree_visualize の実行ファイルを作成
