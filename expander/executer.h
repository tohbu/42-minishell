#ifndef EXECUTER_H
#define EXECUTER_H
#include "../parser/parse.h"
#include "../lexer/lexer.h"
typedef struct s_env_list
{
	char * key;
	char * value;
	struct s_env_list * next;
} t_env_list;

t_env_list *new_env_node(char *in_key, char* in_value);
t_env_list *ft_get_env(char *s);
void search_expand(command_list *com, t_env_list * env);
void expand_env(tree* t, t_env_list* env);
t_env_list *get_envp_to_struct(char *envp[]);
void free_envlist(t_env_list * t);
void print_env_list(t_env_list* t);
#endif
