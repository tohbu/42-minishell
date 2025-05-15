/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 14:39:50 by rseki             #+#    #+#             */
/*   Updated: 2025/05/15 18:44:41 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"

/*
is there "-n" flag?
echo -n "hello"
echo -nnn "hello"
echo -n -n "hello"
*/
static int	is_n_flag(const char *str)
{
	int	i;

	i = 1;
	if (!str || str[0] != '-' || str[1] != 'n')
		return (0);
	while (str[i] == 'n')
		i++;
	return (str[i] == '\0');
}

/*
args[0] = "echo". args[1] == "-n"??
1. is_n_flag?
2. skips the n flag if present.
3. prints the remaining arguments.->print_arg_with_expansion
4. add a newline only if -n was not found.
*/
int	ft_echo(char **args, t_env_list *env)
{
	int	i;
	int	new_line;

	(void)env;
	i = 1;
	new_line = 1;
	while (args[i] && is_n_flag(args[i]))
	{
		new_line = 0;
		i++;
	}
	while (args[i])
	{
		write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (new_line)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
