/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseki <rseki@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 16:25:37 by rseki             #+#    #+#             */
/*   Updated: 2025/05/11 16:25:41 by rseki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

t_builtin   g_builtin[] = {
    {"echo", ft_echo},
    {NULL, NULL}
};

// int g_exit_status = 0;

int	execute_builtin(char *argv[], t_env_list *env)
{
    int          i;

    (void)env;
    i = 0;
    while (g_builtin[i].builtin_name)
    {
        if (!ft_strcmp_builtin(g_builtin[i].builtin_name, argv[0]))
        {
            // g_exit_status = g_builtin[i].foo(argv);
            // return (0);
            return (g_builtin[i].foo(argv));
        }
        i++;
    }
    printf("Not a built-in command.\n");
    return (-1);
}

// Very simple split function for testing
char	**split_input(char *line)
{
	char	**args = malloc(sizeof(char *) * 64);
	int		i = 0;

	char *token = strtok(line, " \t\n");
	while (token)
	{
		args[i++] = token;
		token = strtok(NULL, " \t\n");
	}
	args[i] = NULL;
	return (args);
}

int	main(void)
{
	char	line[1024];
	char	**args;

	while (1)
	{
		printf("echo-test$ ");
		if (!fgets(line, sizeof(line), stdin))
			break;
		args = split_input(line);
		if (args[0] == NULL)
			continue;
		execute_builtin(args, NULL);
	}
	return (0);
}