/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosantos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 14:31:21 by mosantos          #+#    #+#             */
/*   Updated: 2025/12/17 11:39:55 by sgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"
#include <signal.h>

static void	ft_handle_signals(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_main_signals(void)
{
	struct sigaction	act;
	struct sigaction	act_quit;

	ft_bzero(&act, sizeof(act));
	ft_bzero(&act_quit, sizeof(act_quit));
	sigemptyset(&act.sa_mask);
	sigemptyset(&act_quit.sa_mask);
	act.sa_handler = &ft_handle_signals;
	act_quit.sa_handler = SIG_IGN;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act_quit, NULL);
}

void	ft_execute_signals(void)
{
	struct sigaction	act;
	struct sigaction	act_quit;

	ft_bzero(&act, sizeof(act));
	ft_bzero(&act_quit, sizeof(act_quit));
	sigemptyset(&act.sa_mask);
	sigemptyset(&act_quit.sa_mask);
	act.sa_handler = SIG_DFL;
	act_quit.sa_handler = SIG_DFL;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act_quit, NULL);
}

void	ft_ignore_signals(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	sigemptyset(&act.sa_mask);
	act.sa_handler = SIG_IGN;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}

void	ft_heredoc_signals(int child_pid)
{
	struct sigaction	sa_sigint;
	struct sigaction	sa_sigquit;

	sa_sigint.sa_flags = 0;
	sigemptyset(&sa_sigint.sa_mask);
	if (child_pid == 0)
		sa_sigint.sa_handler = SIG_DFL;
	else
		sa_sigint.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa_sigint, NULL);
	sa_sigquit.sa_flags = 0;
	sigemptyset(&sa_sigquit.sa_mask);
	sa_sigquit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa_sigquit, NULL);
}
