#include "executer.h"

// typedef struct s_env_list
// {
// 	char * key;
// 	char * value;
// 	struct env * next;
// } t_env_list;


// void print

char	*ft_strndup(char *s, size_t n)
{
	char	*ret;
	size_t	i;

	i = 0;
	ret = (char *)malloc(n + 1);
	if (!ret)
		return (NULL);
	while (i < n && s[i] != '\0')
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

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
	char * key = ft_strndup( s, ft_strchr(s,'=') - s);
	char *value = ft_strdup(ft_strchr(s,'=')+1);
	return new_env_node(key,value);
}

void print_env_list(t_env_list* t)
{
	if(!t)
	{
		printf("env_list = NULL\n");
	}
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

int main(int argc, char *argv[], char *envp[]) {
	t_env_list *env = get_envp_to_struct(envp);
	print_env_list(env);
	free_envlist(env);
    return 0;
}
