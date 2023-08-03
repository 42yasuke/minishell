/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:58:52 by jose              #+#    #+#             */
/*   Updated: 2023/08/03 17:55:45 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_ginf	*g_inf = NULL;

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
	if (ft_strlen(rl_line_buffer))
	{
		if (!g_inf->is_child_process)
			rl_replace_line(TCHAO, 1);
	}
}

static void	ft_main_suite(char *line, char **envp)
{
	if (!ft_verif_cmd(line))
	{
		write(STDERR_FILENO, "minishell: error redirection or pipe\n", 38);
		g_inf->exit_code = 2;
		return ;
	}
	ft_init_ginf(envp, false);
	line = ft_sd_quote_manager(line);
	g_inf->line = line;
	if (ft_is_builtin_no_pipe(line))
		ft_builtin_no_pipe(line, g_inf->env);
	else
		ft_exec_manager(line, g_inf->env);
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
