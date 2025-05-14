/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:11:44 by tohbu             #+#    #+#             */
/*   Updated: 2025/05/14 21:42:37 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# include <signal.h>

# define ERROR -1
# define TOKEN_END -2
# define SYNTAX_ERROR 1
# define READ_FD 0
# define WRITE_FD 1
# define NO_FILE -1
# define COMAND_NOT_FOUND 127
# define TEMP_BUF_SIZE 32
# define END -2

typedef int					t_bool;
extern int					g_interrupt_state;

enum						e_Token_type
{
	WORD,
	WORD_IN_SINGLE_QOUTE,
	WORD_IN_DOUBLE_QOUTE,
	PIPE,
	AND,
	OR,
	REDIRECT,
	REDIRECT_IN,
	REDIRECT_OUT,
	REDIRECT_APPEND,
	HEARDOC,
};

typedef struct s_token_list
{
	struct s_token_list		*next;
	char					*token;
	int						token_type;
	int						error_flag;
}							t_token_list;

typedef struct s_token_manager
{
	t_token_list			*head;
	t_token_list			*cur;
}							t_token_manager;

typedef struct s_command_list
{
	struct s_command_list	*next;
	char					*s;
	int						token_type;

}							t_command_list;

typedef struct s_tree
{
	struct s_tree			*left;
	struct s_tree			*right;
	int						token_type;
	t_command_list			*com;
	t_command_list			*head;
}							t_tree;

typedef struct s_env_list
{
	char					*key;
	char					*value;
	struct s_env_list		*next;
}							t_env_list;

typedef struct s_pid_list
{
	struct s_pid_list		*next;
	pid_t					pid;

}							t_pid_list;

typedef struct s_minishell
{
	t_env_list				*env;
	t_token_manager			*token;
	t_tree					*ast;
	t_pid_list				*pid_list;
	int						parent_fd[2];
	int						state;
}							t_minishell;

#endif