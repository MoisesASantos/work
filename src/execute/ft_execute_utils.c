/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosantos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:37:25 by mosantos          #+#    #+#             */
/*   Updated: 2025/11/28 13:01:51 by mosantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

int	ft_lstsize_cmd(t_cmd *lst)
{
	int	i;

	i = 0;
	if (!lst)
		return (0);
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

int	*ft_init_child_process(t_cmd *cmd_list)
{
	int	size;
	int	*pid;

	if (!cmd_list)
		return (NULL);
	size = ft_lstsize_cmd(cmd_list);
	pid = malloc(sizeof(pid_t) * size);
	if (!pid)
		return (NULL);
	ft_bzero(pid, sizeof(pid_t) * size);
	return (pid);
}

int	ft_str_equal(const char *str, const char *src)
{
	size_t	size;

	if (!str || !src)
		return (0);
	size = ft_strlen(str);
	if (size != ft_strlen(src))
		return (0);
	return (ft_strncmp(str, src, size) == 0);
}

int	wait_for_single_child(pid_t *child_pid)
{
	int	status;
	int	exit_code;

	exit_code = 0;
	if (waitpid(*child_pid, &status, 0) == -1)
		return (1);
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		exit_code = 128 + WTERMSIG(status);
	return (exit_code);
}

int	wait_for_multiple_children(pid_t *child_pids, int count)
{
	int	status;
	int	exit_code;
	int	i;

	exit_code = 0;
	i = 0;
	while (i < count)
	{
		if (waitpid(child_pids[i], &status, 0) == -1)
		{
			i++;
			continue ;
		}
		if (i == count - 1)
		{
			if (WIFEXITED(status))
				exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				exit_code = 128 + WTERMSIG(status);
		}
		i++;
	}
	free(child_pids);
	return (exit_code);
}
