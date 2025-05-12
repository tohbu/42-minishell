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

typedef int (*t_builtin_func)(char **);

typedef struct s_builtin
{
    const char  *builtin_name;
    int (*foo)(char **, t_env_list *); //protype of every builtin

}   t_builtin;

// builtin.c
int     execute_builtin(char *argv[], t_env_list *env);
char	**split_input(char *line);

// command_echo.c
int     ft_echo(char **args, t_env_list *env);

// command_pwd.c
int     ft_pwd(char **argv, t_env_list *env);

// utilis.c
int     ft_strcmp_builtin(const char *s1, const char *s2);
void     ft_error(const char *msg);
void    p_builtin_error(const char *cmd, const char *msg);
void    Getcwd(char *buf, size_t size);

// main.c
void	print_env_list(t_env_list *t);
t_env_list	*add_new_env(t_env_list *env, char *key, char *value);
char	*ft_strndup(char *s, size_t n);
int	main(int argc, char *argv[], char *envp[]);


