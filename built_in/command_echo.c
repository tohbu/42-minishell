/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseki <rseki@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 14:39:50 by rseki             #+#    #+#             */
/*   Updated: 2025/05/11 14:39:51 by rseki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/*
is there "-n" flag?
echo -n "hello"
echo -nnn "hello"
echo -n -n "hello"
*/
static int  is_n_flag(const char *str)
{
    int i;

    i = 1;
    if (!str || str[0] != '-' || str[1] != 'n')
        return (0);
    while (str[i] == 'n')
        i++;
    return (str[i] == '\0');
}

/*
echo "hello" -> hello
*/
static int remove_quates_and_print(const char *str)
{
    size_t  len;

    len = ft_strlen(str);
    if (len >= 2 && str[0] == '"' && str[len- 1] == '"')
        write(STDOUT_FILENO, str + 1, len -2);
    else
        write(STDOUT_FILENO, str, len);
    return (0);
}

/*
args[0] = "echo". args[1] == "-n"??
1. is_n_flag?
2. skips the n flag if present.
3. prints the remaining arguments.
4. add a newline only if -n was not found.
*/
int ft_echo(char **args)
{
    int i;
    int new_line;

    i = 1;
    new_line = 1;

    while (args[i] && is_n_flag(args[i]))
    {
        new_line = 0;
        i++;
    }
    while (args[i])
    {
        remove_quates_and_print(args[i]);
        if (args[i + 1])
            write(STDOUT_FILENO, " ", 1);
        i++;
    }
    if (new_line)
        write(STDOUT_FILENO, "\n", 1);
    return (0);
}