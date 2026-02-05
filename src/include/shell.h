/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaspar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 10:14:00 by sgaspar           #+#    #+#             */
/*   Updated: 2025/11/28 14:13:39 by mosantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H
# include "../../lib/libft/libft.h"
# include "./ft_cleanup.h"
# include "./ft_execute_cmd.h"
# include "./ft_handle_input.h"
# include "./structs.h"
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# define SHELLNAME "mucua-shell"
# define EXIT_FAILURE 1

extern int	g_signal_received;

t_env	*ft_getenv(t_list *env, char *key);
char	**ft_env_matrix(t_list *env);
char	*join_and_free(char *dest, char *src);
char	*append_char(char *str, char c);
void	clean_empty_strs(char **matrix);
void	ft_env_dump(t_list *env);
void	ft_set_env(t_list **env, char *key, char *value);
void	minishell(t_shell *shell, char **lexer_cmd);
void	ft_init_shell(char **envp, t_shell **shell);
int		load_env_2_shell(char **envp, t_shell *shell);

#endif
