/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaspar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 16:35:55 by sgaspar           #+#    #+#             */
/*   Updated: 2026/01/30 15:38:28 by sgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include "../../lib/libft/libft.h"

typedef struct s_env
{
	char				*key;
	char				*value;
}						t_env;

typedef enum e_redirect_type
{
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_IN,
	REDIR_HEREDOC
}						t_redirect_type;

typedef struct s_redirect
{
	char				*file_name;
	char				*limeter;
	struct s_redirect	*next;
	t_redirect_type		type;
	int					heredoc_fd;
}						t_redirect;

typedef struct s_cmd
{
	t_redirect			*redirects;
	char				**argv;
	struct s_cmd		*next;
}						t_cmd;

typedef struct s_shell
{
	char				*line;
	t_cmd				*cmd;
	t_list				*env;
	int					exit_status;
	int					is_run;
}						t_shell;

#endif
