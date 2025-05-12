/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseki <rseki@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 16:37:11 by rseki             #+#    #+#             */
/*   Updated: 2025/05/11 16:37:13 by rseki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int ft_strcmp_builtin(const char *s1, const char *s2)
{
    size_t i;

    i = 0;
    while (s1[i] != '\0' || s2[i] != '\0')
    {
        if ((unsigned char)s1[i] != (unsigned char)s2[i])
            return ((unsigned char)s1[i] - (unsigned char)s2[i]);
        i++;
    }
    return (0);
}

// erro handling

void ft_error(const char *msg)
{
    write(STDERR_FILENO, "minishell: ", 11);
    write(STDERR_FILENO, msg, ft_strlen(msg));
    write(STDERR_FILENO, "\n", 1);
}

void    p_builtin_error(const char *cmd, const char *msg)
{
    write(STDERR_FILENO, cmd, ft_strlen(cmd));
    write(STDERR_FILENO, ": ", 2);
    write(STDERR_FILENO, msg, ft_strlen(msg));
    write(STDERR_FILENO, "\n", 1);
}

//WRAPPER
void    Getcwd(char *buf, size_t size)
{
    if (getcwd(buf, size) == NULL)
    {
        perror("getcwd FAILED\n");
        exit(1);
    }
}