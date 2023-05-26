/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:58:52 by jose              #+#    #+#             */
/*   Updated: 2023/05/26 20:19:42 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_ginf	*g_inf = NULL;

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

static void	ft_main_suite(char *line, char **env)
{
	line = ft_sd_quote_manager(line);
	g_inf->line = line;
	if(ft_is_builtin_no_pipe(line))
		ft_builtin_no_pipe(line, env);
	else
		ft_exec_manager(line, env);
	ft_free_ginf();
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	char	**env;

	ft_init_ginf(ac, av);
	signal(SIGINT, ft_sigint_handler);
	signal(SIGQUIT, ft_sigquit_handler);
	env = ft_cpy_envp(envp);
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
		ft_main_suite(line, env);
	}
	return (ft_free_all(env), EXIT_SUCCESS);
}
