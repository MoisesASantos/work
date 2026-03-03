/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeronim <cjeronim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 12:43:31 by cjeronim          #+#    #+#             */
/*   Updated: 2026/03/03 13:54:46 by cjeronim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_find_command(char **broke_path, char *token)

{
	int		i;
	char	*cmd_tmp1;
	char	*cmd_tmp2;

	i = 0;
	if (!broke_path)
		return (NULL);
	while (broke_path[i])
	{
		cmd_tmp1 = ft_strjoin(broke_path[i], "/");
		if (!cmd_tmp1)
			return (NULL);
		cmd_tmp2 = ft_strjoin(cmd_tmp1, token);
		free(cmd_tmp1);
		if (!cmd_tmp2)
			return (NULL);
		if (access(cmd_tmp2, X_OK) == 0)
			return (cmd_tmp2);
		free(cmd_tmp2);
		i++;
	}
	return (NULL);
}

char	**env_to_array(t_env *env)

{
	int		size;
	int		i;
	char	**array;
	t_env	*tmp;
	char	*join;

	i = 0;
	size = ft_count_list(env);
	tmp = env;
	array = malloc(sizeof(char *) * (size + 1));
	if (!array)
		return (NULL);
	while (tmp)
	{
		if (tmp->value)
		{
			join = ft_strjoin(tmp->name, "=");
			array[i] = ft_strjoin(join, tmp->value);
			free(join);
			i++;
		}
		tmp = tmp->next;
	}
	array[i] = NULL;
	return (array);
}

static void	exec_child(t_data *data, char **array_env)

{
	char	**broke_path;
	char	*command;
	t_env	*path;

	signals_exec();
	if (to_redirect(data) || !array_env
		|| !data->cmd.cmd_exec || !data->cmd.cmd_exec[0])
		exit(1);
	if (access(data->cmd.cmd_exec[0], X_OK) == 0
		&& execve(data->cmd.cmd_exec[0],
			data->cmd.cmd_exec, array_env) == -1)
		exit(126);
	path = found_name_env(data->b_env, "PATH");
	if (!path || !path->value)
		exit(127);
	broke_path = ft_split(path->value, ':');
	if (!broke_path)
		exit(127);
	command = ft_find_command(broke_path, data->cmd.cmd_exec[0]);
	free_array(broke_path);
	if (!command)
		exit(127);
	if (execve(command, data->cmd.cmd_exec, array_env) == -1)
		exit(126);
	exit (0);
}

static void	handle_parent_status(t_data *data, int status)

{
	if (WIFSIGNALED(status))
		data->status = 128 + WTERMSIG(status);
	else if (WIFEXITED(status))
	{
		data->status = WEXITSTATUS(status);
		if (data->status == 126)
			print_error(data, "Error: command not executable\n", 126);
		else if (data->status == 127)
		{
			ft_putstr_fd(data->cmd.cmd_exec[0], STDERR_FILENO);
			print_error(data, ": command not found", 127);
		}
	}
}

int	execute_if_command_exists(t_data *data)

{
	pid_t	pid;
	int		status;
	char	**array_env;

	array_env = env_to_array(data->b_env);
	pid = fork();
	if (pid == 0)
		exec_child(data, array_env);
	signals_ignore();
	waitpid(pid, &status, 0);
	free_array(array_env);
	signals_mains();
	handle_parent_status(data, status);
	return (1);
}
