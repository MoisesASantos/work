/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosantos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 12:13:40 by mosantos          #+#    #+#             */
/*   Updated: 2026/01/30 15:30:09 by sgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

static void	ft_operiton_heredoc(char *line, int pipefd[2])
{
	if (!line)
	{
		ft_putstr_fd("minishell: warning: here-document at line 1 delimited by \
end-of-file\n", STDOUT_FILENO);
		close(pipefd[1]);
		exit(EXIT_SUCCESS);
	}
}

static void	ft_heredoc_child(t_shell *shell, char *limeter, int pipefd[2])
{
	char	*line;
	char	*tmp;

	close(pipefd[0]);
	ft_heredoc_signals(0);
	if (!limeter)
		exit(EXIT_FAILURE);
	while (1)
	{
		line = readline("> ");
		ft_operiton_heredoc(line, pipefd);
		if (ft_strlen(line) == ft_strlen(limeter)
			&& ft_strncmp(line, limeter, ft_strlen(limeter)) == 0)
		{
			free(line);
			break ;
		}
		tmp = line;
		line = expand_str(shell, line);
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		(free(line), free(tmp));
	}
	(close(pipefd[1]), exit(EXIT_SUCCESS));
}

static int	ft_heredoc_parent(int pipefd[2], pid_t pid, t_redirect *redir)
{
	int	exit_code;
	int	status;

	close(pipefd[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		exit_code = 130;
	else if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	else
		exit_code = 1;
	if (exit_code == EXIT_SUCCESS)
		redir->heredoc_fd = pipefd[0];
	else
		close(pipefd[0]);
	ft_main_signals();
	return (exit_code);
}

int	ft_handle_heredoc(t_shell *shell, t_redirect *redir)
{
	pid_t	pid;
	int		pipefd[2];

	if (!redir || !redir->limeter)
	{
		print_error_msg("heredoc", "missing delimiter");
		return (EXIT_FAILURE);
	}
	if (pipe(pipefd) == -1)
	{
		print_perror_msg("pipe", NULL);
		return (EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		ft_close_pipe(pipefd);
		print_perror_msg("fork", NULL);
		return (EXIT_FAILURE);
	}
	if (pid == 0)
		ft_heredoc_child(shell, redir->limeter, pipefd);
	ft_heredoc_signals(pid);
	return (ft_heredoc_parent(pipefd, pid, redir));
}

void	ft_redir_heredoc(t_redirect *redir)
{
	if (redir && redir->heredoc_fd != -1)
		redirect_fd(redir->heredoc_fd, STDIN_FILENO);
	close(redir->heredoc_fd);
}
