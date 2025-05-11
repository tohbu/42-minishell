/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:03:08 by tohbu             #+#    #+#             */
/*   Updated: 2025/05/07 14:18:04 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/struct.h"

typedef struct s_builtin
{
    const char  *builtin_name;
    int (*foo)(char **); //protype of every builtin

}   t_builtin;

// builtin.c
int	execute_builtin(char *argv[], t_env_list *env);
char	**split_input(char *line);

// command_echo.c
int ft_echo(char **args);

// utilis.c
int ft_strcmp_builtin(const char *s1, const char *s2);

