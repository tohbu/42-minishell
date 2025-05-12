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

static const t_builtin   l_builtin[] = {
    {"echo", ft_echo},
	{"pwd", ft_pwd},
    {NULL, NULL}
};

// Excute built-in command if match
// returns built-in's exit code (0 for success)
// returns -1 if not a built-in
int	execute_builtin(char *argv[], t_env_list *env)
{
    int	i;
	int	exit_status;

    (void)env;
    i = 0;
    while (l_builtin[i].builtin_name)
    {
        if (!ft_strcmp_builtin(l_builtin[i].builtin_name, argv[0]))
        {
            exit_status = l_builtin[i].foo(argv, env);
            return (exit_status);
        }
        i++;
    }
    return (-1);
}

static char *strip_quotes(char *s)
{
    size_t len = ft_strlen(s);

    if (len >= 2 && s[0] == '"' && s[len - 1] == '"')
    {
        s[len - 1] = '\0'; // remove trailing quote
        return s + 1;       // skip leading quote
    }
    return s;
}

// Very simple split function for testing
char	**split_input(char *line)
{
	char	**args;
	int		i = 0;
	char	*token;

	args = malloc(sizeof(char *) * 64);
	if (!args)
		return (NULL);
	token = strtok(line, " \t\n");
	while (token)
	{
		token = strip_quotes(token);
		args[i++] = token;
		token = strtok(NULL, " \t\n");
	}
	args[i] = NULL;
	return (args);
}

// int	main(void)
// {
// 	char	line[1024];
// 	char	**args;

// 	while (1)
// 	{
// 		printf("minishell$ ");
// 		if (!fgets(line, sizeof(line), stdin))
// 			break;
// 		args = split_input(line);
// 		if (!args || !args[0])
// 		{
// 			free(args);
// 			continue ;
// 		}
// 		execute_builtin(args, NULL);
// 		free(args);
// 	}
// 	return (0);
// }