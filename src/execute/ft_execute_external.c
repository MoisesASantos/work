/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_external.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaspar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 12:53:01 by sgaspar           #+#    #+#             */
/*   Updated: 2026/01/15 11:48:16 by sgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/shell.h"
#include <sys/stat.h>

static char	*ft_get_full_path(char *cmd, t_list *env)
{
	t_env	*got_env;
	char	**matrix;
	char	*full_path;
	int		i;

	got_env = ft_getenv(env, "PATH");
	if (!got_env || !got_env->value)
		return (NULL);
	matrix = ft_split(got_env->value, ':');
	i = -1;
	while (matrix[++i])
	{
		full_path = ft_calloc(ft_strlen(matrix[i]) + \
ft_strlen(cmd) + 2, sizeof(char));
		ft_strlcat(full_path, matrix[i], ft_strlen(matrix[i]) + 1);
		ft_strlcat(full_path, "/", ft_strlen(full_path) + 2);
		ft_strlcat(full_path, cmd, ft_strlen(full_path) + ft_strlen(cmd) + 1);
		if (access(full_path, X_OK) == 0)
		{
			ft_free_split((void **)matrix);
			return (full_path);
		}
		free(full_path);
	}
	ft_free_split((void **)matrix);
	return (NULL);
}

static char	*get_path_to_run(char *cmd, t_list *env)
{
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	return (ft_get_full_path(cmd, env));
}

static void	handle_exec_error(char *cmd)
{
	struct stat	path_stat;
	int			exit_code;

	exit_code = 0;
	if (stat(cmd, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		print_error_msg(cmd, "Is a directory");
		exit_code = 126;
	}
	else if (errno == EACCES)
	{
		print_perror_msg(cmd, "Permission denied");
		exit_code = 126;
	}
	else if (errno == ENOENT)
	{
		print_error_msg(cmd, "No such file or directory");
		exit_code = 127;
	}
	else
	{
		print_perror_msg(cmd, NULL);
		exit_code = 1;
	}
	exit(exit_code);
}

void	execute_external(char **argv, void *env)
{
	char	*path;
	char	**matrix;

	path = get_path_to_run(argv[0], env);
	if (!path)
	{
		print_error_msg(argv[0], "command not found");
		ft_free_split((void **)argv);
		exit(127);
	}
	matrix = ft_env_matrix(env);
	execve(path, argv, matrix);
	ft_free_split((void **)matrix);
	handle_exec_error(path);
	exit(1);
}
