/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 22:11:29 by tohbu             #+#    #+#             */
/*   Updated: 2025/04/24 22:11:30 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "lexer.h"

// void	print_t_token_list(t_token_list *head)
// {
// 	t_token_list	*temp;

// 	temp = head;
// 	while (temp)
// 	{
// 		printf("Token_type: %d Token: %s\n", temp->token_type, temp->token);
// 		temp = temp->next;
// 	}
// }

// int	main(void)
// {
// 	// 入力を格納するためのバッファ
// 	char input[1024];

// 	// ユーザーに標準入力を促すメッセージ
// 	printf("Enter a command: ");

// 	// 標準入力から1行読み取る
// 	if (fgets(input, sizeof(input), stdin) == NULL)
// 	{
// 		printf("Error reading input.\n");
// 		return (1);
// 	}

// 	// 入力文字列の末尾の改行を削除
// 	input[strcspn(input, "\n")] = 0;

// 	// トークンリストの初期化
// 	t_token_all *all = (t_token_all *)malloc(sizeof(all));
// 	if (!all)
// 		return (-1);
// 	init_t_token_all(all);
// 	// レキサー関数を呼び出して入力文字列をトークン化
// 	if (lexer(input, all) == ERROR)
// 	{
// 		printf("Error in lexer\n");
// 		return (1);
// 	}

// 	// トークンリストを表示
// 	print_t_token_list(all->head->next);

// 	return (0);
// }