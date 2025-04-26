#ifndef EXECUTER_H
# define EXECUTER_H
# include "../lexer/lexer.h"
# include "../parser/parse.h"
#include "get_next_line.h"
typedef struct s_env_list
{
	char				*key;
	char				*value;
	struct s_env_list	*next;
}						t_env_list;

t_env_list				*new_env_node(char *in_key, char *in_value);
t_env_list				*ft_get_env(char *s);
void					search_expand(t_command_list *com, t_env_list *env);
void					expand_env(t_tree *t, t_env_list *env);
t_env_list				*get_envp_to_struct(char *envp[]);
void					free_envlist(t_env_list *t);
void					print_env_list(t_env_list *t);
char	*ft_strjoin_and_free(char *s1, char *s2);
//
void expand_herdoc(t_command_list* com);
char *heredoc(char * eof);
void search_tree_heredoc(t_tree * t);

#endif
