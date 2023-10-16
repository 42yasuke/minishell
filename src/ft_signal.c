/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jralph <jralph@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 20:25:09 by jose              #+#    #+#             */
/*   Updated: 2023/10/16 12:43:19 by jralph           ###   ########.fr       */
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
	signal(SIGINT, ft_sigint_handler);
	signal(SIGQUIT, ft_sigquit_handler);
}

void	ft_sigint_handler(int sig)
{
	int	dev_null;

	(void)sig;
	dev_null = 0;
	if (g_exit_code == HERE_DOC)
	{
		dev_null = open("/dev/null", O_RDWR);
		g_exit_code = HD_SIGINT;
		(dup2(dev_null, STDIN_FILENO), close(dev_null));
	}
	else
	{
		write(STDIN_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_code = 130;
	}
}

void	ft_sigquit_handler(int sig)
{
	(void)sig;
}
