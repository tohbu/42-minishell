/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoki-koukoukyo <tomoki-koukoukyo@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:49:42 by tohbu             #+#    #+#             */
/*   Updated: 2025/05/19 14:11:28 by tomoki-kouk      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H
# include "minishell.h"
# include "struct.h"

// expander_utils.c ok
char		*ft_strjoin_and_free(char *s1, char *s2);
t_bool		check_env_format(char c);
int			ft_strcmp(const char *s1, const char *s2);
t_env_list	*new_env_node(char *in_key, char *in_value);
t_env_list	*ft_get_env(char *s);
// expander.c ok
char		*match_env_key(char *search, t_env_list *env);
t_env_list	*get_envp_to_struct(char *envp[]); // dumy あり;
char		*expand_all_dollars(char *s, t_env_list *env, int state);
void		expand_env_args_and_state(t_command_list *com, t_env_list *env,
				int state);
void		expand_env(t_tree *t, t_minishell *my_shell);
// heredoc.c ok
void		print_heredoc_warning(char *eof);
char		*heredoc(char *eof);
void		expand_heredoc(t_token_manager *com, t_minishell *my_shell);
t_bool		heredoc_check(t_token_manager *token);

// heredoc_readline.c ok
char		*ft_strdup_extra(char *s);
char		*exted_buf(char *s, int k);
int			ft_getc(int fd);
char		*heredoc_readline(void);
// delete_quote.c
void		delete_quote_com(t_command_list *com);
char		*skip_quotes(char *s, char quote_char);
char		*delete_quote(char *s);
char		*strjoin_token_list(t_token_list *tokne_list);
char		*delete_quote_sub(char *com, t_token_manager *token_mg);
// lexer_for_delete_quote.c
char		*handle_single_quote(char *s, t_token_manager *token);
char		*handle_double_quote(char *s, t_token_manager *token);
char		*handle_word_for_expander(char *s, t_token_manager *token);
t_bool		lexer_for_delete_quote(char *one_line, t_token_manager *token);

// expand_sub.c ok
int			count_same_char(char *s, char c);
char		*join_last_status_with_back(char *front, char *back, int state);

char		*join_env_vars_with_back(char *front, char *back, char *key,
				t_env_list *env);
char		*result_expand_str(char *s, char *tmp, int state, t_env_list *env);
char		*expand_env_or_status(char *s, t_env_list *env, int state, int i);

#endif
