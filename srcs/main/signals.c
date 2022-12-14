/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 21:21:41 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/09/28 11:24:41 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_handler(int sig);

/* Handle SIGINT (Ctrl + C) signals */
void	sigint_handler(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_data.status = 130;
}

/* Set sigactions to properly invoke its handler */
void	main_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = &sigint_handler;
	sa_int.sa_flags = SA_RESTART;
	sigemptyset(&sa_int.sa_mask);
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = 0;
	sigemptyset(&sa_quit.sa_mask);
	sigaction(SIGQUIT, &sa_quit, NULL);
}

void	executor_signals(int pid, int f)
{
	struct sigaction	sa;

	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (!pid && f)
		sa.sa_handler = SIG_DFL;
	else
		sa.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

static void	heredoc_handler(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', 1);
	clean_data(&g_data);
	clean_processes(&g_data.procs);
	ft_lstclear(&g_data.exec_data, clean_s_cmd);
	ft_lstclear(&g_data.lst_env, free);
	rl_clear_history();
	exit(130);
}

void	heredoc_signals(int pid, int f)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_flags = 0;
	sigemptyset(&sa_int.sa_mask);
	if (!pid && f)
		sa_int.sa_handler = &heredoc_handler;
	else
		sa_int.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_flags = 0;
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sigaction(SIGQUIT, &sa_quit, NULL);
}
