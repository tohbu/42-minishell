/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:01:48 by rseki             #+#    #+#             */
/*   Updated: 2025/05/14 21:30:08 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"

static int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static long long	ft_atoll(const char *str, int *error)
{
	long long	result;
	int			sign;
	int			i;

	result = 0;
	sign = 1;
	i = 0;
	*error = 0;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (result > (LLONG_MAX / 10))
			*error = 1;
		result = result * 10 + (str[i] - '0');
		if (result < 0)
			*error = 1;
		i++;
	}
	return (result * sign);
}

static void	p_exit_custum_error(const char *arg1, const char *arg2)
{
	write(STDERR_FILENO, "exit\nminishell: exit: ", 22);
	write(STDERR_FILENO, arg1, ft_strlen(arg1));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, arg2, ft_strlen(arg2));
	write(STDERR_FILENO, "\n", 1);
}

static int	ft_check_args(char **argv, long long *exit_status)
{
	int	error;

	error = 0;
	if (!is_numeric(argv[1]))
	{
		// p_builtin_error("exit", "numeric argument required");
		// write(STDERR_FILENO, "exit: ", 6);
		p_exit_custum_error(argv[1], "numeric argument required");
		exit(255);
	}
	*exit_status = ft_atoll(argv[1], &error);
	if (error)
	{
		p_exit_custum_error(argv[1], "numeric argument required");
		exit(255);
	}
	if (argv[2])
	{
		write(2, "exit\n", 5);
		p_builtin_error("exit", "too many arguments");
		return (1);
	}
	return (0);
}

/*
Exit
1 No arguments -> exit with last status or 0
2 Check if first argument is numeric
	if not -> print error, free resources, exit(255)
3 If more than 1 argument
	print error, return 1 without exiting (bash behavior)
4 Convert argument to long long safely (handle overflow)
5 Clean up env and any global resources
6 exit with (exit_status % 256)
*/
int	ft_exit(char **argv, t_env_list *env)
{
	long long	exit_status;
	int			error;

	exit_status = 0;
	error = 0;
	if (argv[1])
	{
		if (ft_check_args(argv, &exit_status))
			return (1);
	}
	if (!argv[1])
		exit_status = 0;
	free_args(argv);
	free_env(env);
	env = NULL;
	exit(exit_status % 256);
	return (0);
}
