/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:58:52 by jose              #+#    #+#             */
/*   Updated: 2023/09/26 20:59:27 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_ginf	*g_inf = NULL;

static void	ft_main_suite(char *line, char **envp)
{
	if (!ft_verif_line(line, true))
		return ;
	ft_init_ginf(envp, false);
	line = ft_sd_quote_manager(line);
	g_inf->line = line;
	if (!ft_verif_line(line, false))
		return (ft_free_ginf(false));
	if (line)
	{
		if (!ft_strchr(line, PIPE) && ft_is_builtin_no_pipe(line))
			ft_builtin_no_pipe(line, g_inf->env);
		else
			ft_exec_manager(line, g_inf->env);
	}
	ft_free_ginf(false);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;

	(void)av;
	rl_catch_signals = 0;
	if (ac > 1)
		ft_error(BAD_PARAMETERS, "parameters", "bad usage");
	signal(SIGINT, ft_sigint_handler);
	signal(SIGQUIT, ft_sigquit_handler);
	ft_init_ginf(envp, true);
	while (true)
	{
		line = readline("minishell$ ");
		if (!line || !ft_strncmp(line, TCHAO, ft_strlen(TCHAO)))
			break ;
		while (line && ft_is_whitespace(*line))
			line++;
		if (!ft_strncmp(line, "", 1))
			continue ;
		(add_history(line), ft_main_suite(line, envp));
	}
	return (ft_printf("exit\n"), ft_free_ginf(true), EXIT_SUCCESS);
}
