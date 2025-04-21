#ifndef LEXER_H
#define LEXER_H
#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef int				t_bool;

#define ERROR -1
#define TOKEN_END -2

enum					Token_type
{
	WORD,
	WORD_IN_SINGLE_QOUTE,
	WORD_IN_DOUBLE_QOUTE,
	PIPE,
	REDIRECT,
	HEARDOC,
	FILENAME,
	LIMITER,	
};

typedef struct token_list
{
	struct token_list	*next;
	char				*token;
	int					token_type;
	int					syntax_error;
}						token_list;

typedef struct token_all
{
	token_list			*head;
	token_list			*cur;
	int					pipe_n;
}						token_all;

t_bool					lexer(char *one_line, token_all *all);
token_list				*add_list(char *s);
token_all* init_token_all(token_all *all);

t_bool	check_meta_word(char c);
t_bool	check_space(char c);
t_bool	check_quote(char c);

char					*ft_strndup(char *s, size_t n);
int						get_token_type(char *s);
#endif
