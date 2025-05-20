/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_execute_builtin.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 16:25:37 by rseki             #+#    #+#             */
/*   Updated: 2025/05/14 21:32:04 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"

int	execute_builtin(char **argv, t_env_list *env)
{
	int	result;

	if (!argv || !argv[0])
		return (-1);
	if (ft_strcmp_builtin(argv[0], "echo") == 0)
		result = (ft_echo(argv, env));
	else if (ft_strcmp_builtin(argv[0], "pwd") == 0)
		result = (ft_pwd(argv, env));
	else if (ft_strcmp_builtin(argv[0], "env") == 0)
		result = (ft_env(argv, env));
	else if (ft_strcmp_builtin(argv[0], "exit") == 0)
		result = (ft_exit(argv, env));
	else if (ft_strcmp_builtin(argv[0], "cd") == 0)
		result = (ft_cd(argv, env));
	else if (ft_strcmp_builtin(argv[0], "export") == 0)
		result = (ft_export(argv, env));
	else if (ft_strcmp_builtin(argv[0], "unset") == 0)
		result = (ft_unset(argv, env));
	else
		result = (-1);
	free_args(argv);
	return (result);
}

// remove trailing quote
// skip leading quote
static char	*strip_quotes(char *s)
{
	size_t	len;

	len = ft_strlen(s);
	if (len >= 2 && s[0] == '"' && s[len - 1] == '"')
	{
		s[len - 1] = '\0';
		return (s + 1);
	}
	return (s);
}

// Very simple split function for testing
char	**split_input(char *line)
{
	char	**args;
	int		i;
	char	*token;
	char	*stripped;

	i = 0;
	args = malloc(sizeof(char *) * 64);
	if (!args)
		return (NULL);
	token = strtok(line, " \t\n");
	while (token)
	{
		stripped = strip_quotes(token);
		args[i++] = ft_strdup(stripped);
		token = strtok(NULL, " \t\n");
	}
	args[i] = NULL;
	return (args);
}
