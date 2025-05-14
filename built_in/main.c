/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:08:12 by tohbu             #+#    #+#             */
/*   Updated: 2025/05/14 21:31:59 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"
#include "../include/minishell.h"

void	print_env_list(t_env_list *t)
{
	while (t)
	{
		printf("key:%s value: %s\n", t->key, t->value);
		t = t->next;
	}
	printf("------------end env--------------------\n");
}

t_env_list	*add_new_env(t_env_list *env, char *key, char *value)
{
	t_env_list	*tmp;

	tmp = env;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = new_env_node(key, value);
	return (env);
}

char	*ft_strndup(char *s, size_t n)
{
	char	*ret;
	size_t	i;

	i = 0;
	ret = (char *)malloc(n + 1);
	if (!ret)
		return (NULL);
	while (i < n && s[i] != '\0')
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

// int	main(int argc, char *argv[], char *envp[])
// {
// 	t_env_list	*my_env;

// 	(void)argc;
// 	(void)argv;
// 	my_env = get_envp_to_struct(envp);
// 	print_env_list(my_env->next);
// 	my_env = add_new_env(my_env, "NEW_ENV", "minishell");
// 	print_env_list(my_env->next);
// }
