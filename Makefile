# プログラム名
NAME = minishell

# ディレクトリの定義
PARSER_DIR = ./parser
LEXER_DIR = ./lexer
INCLUDE_DIRS = $(PARSER_DIR) $(LEXER_DIR)  # ヘッダーファイルディレクトリ

# ソースファイル
SRCS = main.c $(PARSER_DIR)/parse.c $(LEXER_DIR)/token.c

# オブジェクトファイル
OBJS = $(SRCS:.c=.o)

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
	make clean -C ./libft

fclean: clean
	rm -f $(NAME)
	make fclean -C ./libft
	rm libft.a

re: fclean all
