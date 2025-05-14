/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseki <rseki@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:15:12 by rseki             #+#    #+#             */
/*   Updated: 2025/05/13 09:15:16 by rseki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	init_env(char *envp[], t_env_list **my_env)
{
	*my_env = get_envp_to_struct(envp);
	if (!*my_env)
	{
		ft_error("Failed to initialize env list");
		return (1);
	}
	return (0);
}

static void	minishell_loop(t_env_list *env)
{
	char	line[BUFSIZ];
	char	**args;

	while (1)
	{
		args = NULL;
		ft_putstr_fd("minishell$ ", STDOUT_FILENO);
		if (!fgets(line, sizeof(line), stdin))
			break ;
		args = split_input(line);
		if (args && args[0])
			execute_builtin(args, env);
		if (args)
			free_args(args);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_env_list	*my_env;

	(void)argc;
	(void)argv;
	if (init_env(envp, &my_env))
		return (1);
	minishell_loop(my_env);
	free_env(my_env);
	return (0);
}
