/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_input.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosantos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 11:54:18 by mosantos          #+#    #+#             */
/*   Updated: 2025/11/28 14:18:34 by mosantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_HANDLE_INPUT_H
# define FT_HANDLE_INPUT_H

typedef struct s_shell		t_shell;
typedef struct s_cmd		t_cmd;
typedef struct s_redirect	t_redirect;
typedef struct s_list		t_list;

// error syntax functions
bool						ft_unclosed_quote(char *str);
bool						ft_pipe_error(char *str);
bool						ft_redirect_error(char *str);
bool						ft_invalid_operator(char *str);
bool						ft_parenthesis_error(char *str);
int							ft_syntax_error(char *str);
// parsing funcions
void						ft_create_cmd(t_cmd **cmd);
void						ft_lstadd_cmd(t_cmd **lst, t_cmd *novo);
void						ft_lstadd_redir(t_redirect **lst, t_redirect *novo);
char						*ft_remove_quotes(char *str);
int							is_pipe_token(char *token);
int							ft_skip_quote(char *str, int i);
int							ft_read_command(t_shell *shell);
int							is_redirect_token(char *token);
int							ft_count_args(char **tokens, int *index);
int							ft_parse(char **tokens, t_cmd **cmd_list);
// read input functions
int							ft_read_command(t_shell *shell);
// lexer functions
char						**ft_strip_token(char *str);
char						**lexer(t_shell *shell, char *line);
int							ft_is_token(char c);
int							ft_count_word2split(char *str);
// expand functions
char						**expand_variable(t_shell *shell, char **matrix);
char						*expand_str(t_shell *shell, char *line);
// signals functions
void						ft_main_signals(void);
void						ft_execute_signals(void);
void						ft_ignore_signals(void);
void						ft_heredoc_signals(int child_pid);

#endif
