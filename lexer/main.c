#include "lexer.h"

void print_token_list(token_list *head) {
    token_list *temp = head;
    while (temp) {
        printf("Token_type: %d Token: %s\n",temp->token_type,temp->token);
        temp = temp->next;
    }
}

int main() {
    // 入力を格納するためのバッファ
    char input[1024];

    // ユーザーに標準入力を促すメッセージ
    printf("Enter a command: ");

    // 標準入力から1行読み取る
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Error reading input.\n");
        return 1;
    }

    // 入力文字列の末尾の改行を削除
    input[strcspn(input, "\n")] = 0;

    // トークンリストの初期化
    token_all *all = (token_all*)malloc(sizeof(all));
	if(!all)
		return -1;
	init_token_all(all);
    // レキサー関数を呼び出して入力文字列をトークン化
    if (lexer(input, all) == ERROR) {
        printf("Error in lexer\n");
        return 1;
    }

    // トークンリストを表示
    print_token_list(all->head->next);

    return 0;
}