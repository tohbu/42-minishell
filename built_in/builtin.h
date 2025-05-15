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

// parse_and_execute_builtin.c
int			execute_builtin(char **argv, t_env_list *env);
char		**split_input(char *line);

// command_echo.c
int			ft_echo(char **args, t_env_list *env);

// command_pwd.c
void		Getcwd(char *buf, size_t size);
int			ft_pwd(char **argv, t_env_list *env);

// command_env.c
int			ft_env(char **argv, t_env_list *env);

// command_exit.c
int			ft_exit(char **argv, t_env_list *env);

// command_cd.c
int			ft_cd(char **argv, t_env_list *env);

// command_export.c
int			is_valid_identifier(const char *arg);
int			ft_export(char **argv, t_env_list *env);

// command_export_utilis.c
char		**convert_env_list_to_sorted_array(t_env_list *env);

// command_unset.c
int			ft_unset(char **argv, t_env_list *env);

// utilis.c
int			ft_strcmp_builtin(const char *s1, const char *s2);
void		ft_error(const char *msg);
void		p_builtin_error(const char *cmd, const char *msg);
void		p_builtin_error_no_minishell(const char *cmd, const char *msg);
char		*extract_key(const char *arg);

// main_builtin.c
int			main(int argc, char *argv[], char *envp[]);

// env.c
char		*match_env_key(char *search, t_env_list *env);
char		*expand_command_str(char *s, t_env_list *env);
t_env_list	*get_envp_to_struct(char *envp[]);

// free.c
void		free_args(char **args);
void		free_env(t_env_list *env);

// ft_setenv.c
int			ft_setenv(t_env_list *env, const char *key, char *value);

// main.c
char		*ft_strndup(char *s, size_t n);