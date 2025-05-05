/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 22:10:04 by tohbu             #+#    #+#             */
/*   Updated: 2025/05/05 20:05:52 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "minishell.h"
# include "struct.h"

t_bool			lexer(char *one_line, t_token_all *all);
t_token_list	*add_list(char *s);
t_token_all		*init_t_token_all(void);

t_bool			check_meta_word(char c);
t_bool			check_space(char c);
t_bool			check_quote(char c);

char			*ft_strndup(char *s, size_t n);
int				get_token_type(char *s);
int				ft_strcmp(char *s1, char *s2);
#endif
