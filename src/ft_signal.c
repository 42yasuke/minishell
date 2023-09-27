/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 20:25:09 by jose              #+#    #+#             */
/*   Updated: 2023/09/26 20:53:47 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_ignore_these_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_make_attention_these_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	ft_sigint_handler(int sig)
{
	int	dev_null;

	(void)sig;
	dev_null = 0;
	if (!g_inf->is_child_process)
	{
		write(STDIN_FILENO, "\n", 1);
		rl_clear_history();
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (g_inf->here_doc)
	{
		dev_null = open("/dev/null", O_RDWR);
		g_inf->here_doc_quit = true;
		g_inf->tmp_stdin = dup(STDIN_FILENO);
		(dup2(dev_null, STDIN_FILENO), close(dev_null));
	}
	else
		write(STDIN_FILENO, "\n", 1);
}

void	ft_sigquit_handler(int sig)
{
	(void)sig;
}
