/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 22:10:04 by tohbu             #+#    #+#             */
/*   Updated: 2025/05/05 21:47:53 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "minishell.h"
# include "struct.h"

// token.c
t_bool			lexer(char *one_line, t_token_manager *token);
t_token_list	*add_list(char *s);
t_token_manager	*init_t_token_manager(void);

// token_utils.c
t_bool			check_meta_word(char c);
t_bool			check_space(char c);
t_bool			check_quote(char c);
char			*ft_strndup(char *s, size_t n);
int				get_token_type(char *s);
//
#endif
