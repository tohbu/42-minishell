/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 22:10:04 by tohbu             #+#    #+#             */
/*   Updated: 2025/05/04 17:52:15 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "../libft/libft.h"
# include <errno.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef int				t_bool;
extern int				g_interrupt_state;

# define ERROR -1
# define TOKEN_END -2

enum					e_Token_type
{
	WORD,
	WORD_IN_SINGLE_QOUTE,
	WORD_IN_DOUBLE_QOUTE,
	PIPE,
	REDIRECT,
	REDIRECT_IN,
	REDIRECT_OUT,
	REDIRECT_APPEND,
	HEARDOC,
};

typedef struct s_token_list
{
	struct s_token_list	*next;
	char				*token;
	int					token_type;
	int					syntax_error;
}						t_token_list;

typedef struct s_token_all
{
	t_token_list		*head;
	t_token_list		*cur;
	int					pipe_n;
}						t_token_all;

t_bool					lexer(char *one_line, t_token_all *all);
t_token_list			*add_list(char *s);
t_token_all				*init_t_token_all(t_token_all *all);

t_bool					check_meta_word(char c);
t_bool					check_space(char c);
t_bool					check_quote(char c);

char					*ft_strndup(char *s, size_t n);
int						get_token_type(char *s);
#endif
