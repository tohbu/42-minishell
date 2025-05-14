/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 19:05:42 by tohbu             #+#    #+#             */
/*   Updated: 2025/05/14 15:43:52 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../include/minishell.h"

// // printing out the env list
// // static void	debug_env_list(t_env_list *env)
// // {
// // 	while (env)
// // 	{
// // 		printf("Node at %p\n", env);
// // 		if (env->key)
// // 			printf("  key = %s\n", env->key);
// // 		else
// // 			printf("  key is NULL\n");
// // 		env = env->next;
// // 	}
// // }

// // サーチに入れた環境変数があるかどうかを確認する、あればその文字列をかえす
// char	*match_env_key(char *search, t_env_list *env)
// {
// 	t_env_list	*tmp;

// 	tmp = env;
// 	printf("segf = %s\n", search);
// 	// debug_env_list(env);
// 	while (tmp)
// 	{
// 		if (tmp->key && ft_strcmp(tmp->key, search) == 0)
// 			return (ft_strdup(tmp->value));
// 		tmp = tmp->next;
// 	}
// 	return (ft_calloc(sizeof(char *), 1));
// }

// /*
// replaces the first $VAR found inside the string s with the actual value from env
// 1. find the first $
// 2. if no $ or it is the last char, return s
// 3. split the s into parts
// 	s = "Hello $USER world"
// 	front = "Hello "
// 	tmp = "USER"
// 	back = " world"
// 4. extract the variable name by match_env_key
// 5. return "Hello <VALUE> world"
// */
// char	*expand_command_str(char *s, t_env_list *env)
// {
// 	char	*tmp;
// 	int		i;
// 	char	*front;
// 	char	*back;
// 	char	*result;

// 	tmp = s;
// 	i = 0;
// 	while (*tmp && *tmp != '$')
// 		tmp++;
// 	if (!*tmp || !*(tmp + 1))
// 		return (s);
// 	front = ft_strndup(s, (tmp++ - s));
// 	while (check_env_format(tmp[i]))
// 		i++;
// 	back = ft_strdup(tmp + i);
// 	tmp = ft_strndup(tmp, i);
// 	result = ft_strjoin_and_free(front, match_env_key(tmp, env));
// 	result = ft_strjoin_and_free(result, back);
// 	free(tmp);
// 	return (result);
// }

// // 自分の構造体に構造体を格納する　dumyありのリストで一番はじめはからのノード
// // free the memory malloc by ft_get_env if failed.
// t_env_list	*get_envp_to_struct(char *envp[])
// {
// 	int			i;
// 	t_env_list	*st_env;
// 	t_env_list	*tmp;
// 	t_env_list	*new_node;

// 	i = 0;
// 	st_env = new_env_node(NULL, NULL);
// 	if (!st_env)
// 		return (NULL);
// 	tmp = st_env;
// 	while (envp[i])
// 	{
// 		new_node = ft_get_env(envp[i]);
// 		if (!new_node)
// 		{
// 			// free_env(st_env);
// 			return (NULL);
// 		}
// 		tmp->next = new_node;
// 		tmp = new_node;
// 		i++;
// 	}
// 	return (st_env);
// }
