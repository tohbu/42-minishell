/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohbu <tohbu@student.42.jp>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 22:15:30 by tohbu             #+#    #+#             */
/*   Updated: 2025/05/08 22:28:32 by tohbu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# include "minishell.h"
# include "struct.h"

// parser_utils.c
t_command_list	*new_t_command_list(char *str, int type);
t_tree			*new_node(t_tree *l, t_tree *r, int t_type, char *s);
t_bool			syntax_check(t_token_manager *token, t_tree *t);
t_bool			set_syntax_error(t_token_manager *token);
t_tree			*init_node(void);

// parser.c
void			redirect(t_token_manager *token, t_command_list *com);
void			string(t_token_manager *token, t_command_list *com);
t_tree			*command(t_token_manager *token);
t_tree			*piped_commands(t_token_manager *token);
t_tree			*and_or_node(t_token_manager *token);
t_bool			is_token_word(t_token_list *t);
//

#endif
