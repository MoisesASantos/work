/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleanup.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosantos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 19:40:25 by mosantos          #+#    #+#             */
/*   Updated: 2025/11/28 14:12:39 by mosantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CLEANUP_H
# define FT_CLEANUP_H
# include "structs.h"

void	ft_free_split(void **argv);
void	ft_free_env(void *content);
void	ft_error_msg(char *str, char *src);
void	ft_cleanup_shell(t_shell *shell);
void	ft_lstclean_redirect(t_redirect **redir);
void	print_perror_msg(char *cmd, char *arg);
void	ft_lstclean_cmd(t_cmd **lst, void (*del)(void**));
void	print_error_msg(char *command, char *msg);

#endif
