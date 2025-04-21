#include <stdio.h>
#include <stdlib.h>
#include "./lexer/lexer.h"
#include "./parser/parse.h"

// 再帰的にノードを出力する関数
void print_dot_tree(tree *t, int *node_id) {
    if (!t) return;

    // ノードIDを一意に管理
    int current_node_id = (*node_id)++;
    const char *node_type;

    // ノードタイプを文字列に変換
    if (t->token_type == PIPE)
        node_type = "PIPE";
    else
        node_type = "COMMAND";
    // ノードのラベル（トークンも含めると視覚的にわかりやすい）
    printf("    node%d [label=\"%s\"];\n", current_node_id, node_type);
    if (t->left) 
	{
        int left_node_id = (*node_id)++;
        printf("    node%d -> node%d;\n", current_node_id, left_node_id);
        print_dot_tree(t->left, node_id);  // 再帰的に左の子ノードを出力
    }
    // 右の子ノードがあれば、再帰的に処理
    if (t->right) {
        int right_node_id = (*node_id)++;
        printf("    node%d -> node%d;\n", current_node_id, right_node_id);
        print_dot_tree(t->right, node_id);  // 再帰的に右の子ノードを出力
    }
}

// dot形式でASTを出力する関数
void output_dot(tree *t) {
    int node_id = 0;  // node_idの初期化
    printf("digraph AST {\n");
    print_dot_tree(t, &node_id);  // 再帰的にASTを出力
    printf("}\n");
}

// メイン関数
int main(int argc, char *argv[]) {
    // 入力を格納するためのバッファ
    char input[1024];
    
    argc++;
    argc--; // この部分は不要ですが、スタイルに合わせてそのまま

    while (1) {
        printf("%s> ", argv[0]);

        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("Error reading input.\n");
            return 1;
        }
        input[strcspn(input, "\n")] = 0;  // 改行を取り除く
        
        // トークンリストの初期化
        token_all *all = (token_all*)malloc(sizeof(*all));
        if (!all) {
            printf("Memory allocation error\n");
            return 1;
        }
        init_token_all(all);

        // レキサー関数を呼び出して入力文字列をトークン化
        if (lexer(input, all) == ERROR) {
            printf("Error in lexer\n");
            return 1;
        }

        // 構文解析
        tree* ast = piped_commands(all);
        
        // dot形式でASTを出力
        output_dot(ast);
    }

    return 0;
}
