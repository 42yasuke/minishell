/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:58:52 by jose              #+#    #+#             */
/*   Updated: 2023/05/21 00:12:27 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_sigint_handler(int sig)
{
	(void)sig;
	write(STDIN_FILENO, "\n", 1);
	rl_clear_history();
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_sigquit_handler(int sig)
{
	(void)sig;
	(ft_printf("\nexit\n"), exit(EXIT_SUCCESS));
}

int	main(void)
{
	char	*line;

	signal(SIGINT, ft_sigint_handler);
	signal(SIGQUIT, ft_sigquit_handler);
	while (true)
	{
		line = readline("minishell$ ");
		if (!line)
			(ft_printf("exit\n"), exit(EXIT_SUCCESS));
		while (line && ft_is_whitespace(*line))
			line++;
		if (!ft_strncmp(line, "", 1))
			continue ;
		add_history(line);
		if (!ft_strncmp(line, "cd", 2))
			ft_cd_no_pipe(line);
		else
			ft_exec_manager(line);
		free(line);
	}
	return (EXIT_SUCCESS);
}
