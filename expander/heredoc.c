#include "executer.h"


char *heredoc(char * eof)
{
	char *reslut = ft_calloc(sizeof(char*),1);
	char *buf;
	printf("eof = %s\n",eof);
	while(1)
	{

		write(1,">",1);
		buf = get_next_line(STDIN_FILENO);
		if(!buf)
		return NULL;
		if(buf && ft_strncmp(buf,eof,ft_strlen(buf)-1)==0)
		{
			free(buf);
			free(eof);
			return reslut;
		}
		reslut = ft_strjoin_and_free(reslut,buf);
	}
	return NULL;
}

void expand_herdoc(t_command_list* com)
{
	t_command_list* tmp = com->next;
	while(tmp)
	{
		if(tmp->token_type == HEARDOC)
		{
			printf("in headoc\n");
			tmp->next->s = heredoc(tmp->next->s);
			tmp = tmp->next;
		}
		tmp = tmp->next;
	}	
}

void search_tree_heredoc(t_tree * t)
{
	if(!t)
		return;
	search_tree_heredoc(t->left);
	search_tree_heredoc(t->right);
	expand_herdoc(t->head->next);	
}