# 実行ファイル名
NAME = main

# コンパイラとフラグ
CC = cc
CFLAGS = -Wall -Wextra -Werror

# ソースファイルとオブジェクトファイル
SRCS = main.c env.c expander_utils.c
OBJS = $(SRCS:.c=.o)

# 依存ライブラリ
LIBFT = libft.a
LIBFT_DIR = .

# ヘッダファイル
INCLUDES = -I.

# 実行ファイル生成ルール
$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) -o $(NAME)

# オブジェクトファイルのビルドルール
%.o: %.c built_in.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# libft.a が存在しない場合の対処（オプション）
$(LIBFT):
	@echo "libft.a が見つかりません。別途コンパイルしてください。"

# make all
all: $(NAME)

# make clean
clean:
	rm -f $(OBJS)

# make fclean
fclean: clean
	rm -f $(NAME)

# make re
re: fclean all

.PHONY: all clean fclean re
