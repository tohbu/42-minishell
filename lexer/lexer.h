#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int t_bool;

#define ERROR -1

enum Token_type
{
	WORD,
	WORD_IN_SINGLE_QOUTE,
	WORD_IN_DOUBLE_QOUTE,
	PIPE,
	REDIRECT,
	HEARDOC

};

typedef struct token_list
{
	struct  token_list* next;
	char *token;
	int token_type;
} token_list;

typedef struct  token_all
{
	token_list* head;
	token_list* cur;
	int pipe_n;
} token_all;

t_bool lexer(char * one_line, token_all * all);