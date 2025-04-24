#include "executer.h"

// char	*ft_strndup(char *s, size_t n)
// {
// 	char	*ret;
// 	size_t	i;

// 	i = 0;
// 	int len = ft_strlen(s);
// 	if(len < n)
// 		n = len;
// 	ret = (char *)malloc(n + 1);
// 	if (!ret)
// 		return (NULL);
// 	while (i < n && s[i] != '\0')
// 	{
// 		ret[i] = s[i];
// 		i++;
// 	}
// 	ret[i] = '\0';
// 	return (ret);
// }

t_env_list *new_env_node(char *in_key, char* in_value)
{
	t_env_list* new;
	new =(t_env_list*) malloc(sizeof(t_env_list));
	if(!new)
		return NULL;
	new->key = in_key;
	new->value = in_value;
	new->next = NULL;
	return new;
}

t_env_list *ft_get_env(char *s)
{
	if(!*s)
		return NULL;
	char * key = ft_strndup(s, ft_strchr(s,'=') - s);
	char *value = ft_strdup(ft_strchr(s,'=')+1);
	return new_env_node(key,value);
}


char * match_env_key(char * search , t_env_list * env)
{
	t_env_list * tmp = env;
	while(tmp)
	{
		if(strcmp(tmp->key, search)==0)
			return ft_strdup(tmp->value);
		tmp = tmp->next;
	}
	return NULL;
}

void search_expand(command_list *com, t_env_list * env)
{
	command_list * tmp_com = com;
	while(tmp_com)
	{
		char* str = tmp_com->s;
		while( str && *str && *str != '$')
			str++;
		if(!str || !*str )
		{
			tmp_com = tmp_com->next;
			continue;
		}
		else
		{
			str++;
			int i = 0;
			while(str[i])
			{
				char* tmp = ft_strndup(str,(i+1));
				char *value_tmp = match_env_key(tmp,env);
				printf("\nsearch expand = %s\n",tmp);
				if(value_tmp != NULL)
				{
					printf("ok\n");
					char *dast = tmp_com->s;
					tmp_com->s = ft_strdup(value_tmp);
					free(tmp);
					free(dast);
					break;
				}
				i++;
			}
		}
		tmp_com = tmp_com->next;
	}
}

void expand_env(tree* t, t_env_list* env)
{
	if(!t)
		return ;
	expand_env(t->left, env);
	expand_env(t->right,env);
	search_expand(t->head, env);
	return;
}

void print_env_list(t_env_list* t)
{
	while(t)
	{
		printf("key:%s value: %s\n",t->key, t->value);
		t = t->next;
	}
}
t_env_list *get_envp_to_struct(char *envp[]) //dumy あり
{
	int i = 0;
	t_env_list* st_env;
    st_env = new_env_node(NULL,NULL);
	t_env_list* tmp  = st_env;
	while(envp[i])
	{
		tmp->next = ft_get_env(envp[i]);
		if(!tmp->next)
			return NULL;
		tmp = tmp->next;
		i++;
	}
	return st_env;
}

void free_envlist(t_env_list * t)
{
	if(!t)
		return;
	free_envlist(t->next);
	free(t->key);
	free(t->value);
	free(t);
}

#include <stdio.h>

// int main(int argc, char *argv[], char *envp[]) {
// 	t_env_list *env = get_envp_to_struct(envp);
// 	print_env_list(env);
// 	free_envlist(env);
//     return 0;
// }
