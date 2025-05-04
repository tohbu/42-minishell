/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:49:42 by tohbu             #+#    #+#             */
/*   Updated: 2025/05/04 14:44:22 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H
# include "../lexer/lexer.h"
# include "../parser/parse.h"
# include "get_next_line.h"
# include <readline/history.h>
# include <readline/readline.h>

typedef struct s_env_list
{
	char				*key;
	char				*value;
	struct s_env_list	*next;
}						t_env_list;

t_bool					check_env_format(char c);
t_env_list				*new_env_node(char *in_key, char *in_value);
t_env_list				*ft_get_env(char *s);
char					*match_env_key(char *search, t_env_list *env);
char					*ft_strjoin_and_free(char *s1, char *s2);
char					*expand_command_str(char *s, t_env_list *env);
void					search_expand(t_command_list *com, t_env_list *env);
void					expand_env(t_tree *t, t_env_list *env);
void					print_env_list(t_env_list *t);
t_env_list				*get_envp_to_struct(char *envp[]); // dumy あり;
void					free_envlist(t_env_list *t);
// heredoc.c
char					*delete_quote_for_heredoc(char *s);
char					*heredoc(char *eof);
void					expand_heredoc(t_command_list *com);

void					delete_quote_com(t_command_list *com);
char					*delete_quote(char *s);
void					signal_handle_parent_c(int sig);

#endif
