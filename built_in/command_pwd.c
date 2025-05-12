/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseki <rseki@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:20:34 by rseki             #+#    #+#             */
/*   Updated: 2025/05/12 12:20:35 by rseki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/*
pwd
->print name of current/working directory
*/
int ft_pwd(char **argv, t_env_list *env)
{
    char   cwd[BUFSIZ];

    (void)env;
    if (argv[1])
    {
        p_builtin_error("pwd", "too many arguments");
        return (1);
    }
    Getcwd(cwd, sizeof(cwd));
    write(STDOUT_FILENO, cwd, ft_strlen(cwd));
    write(STDOUT_FILENO, "\n", 1);
    return (0);
}