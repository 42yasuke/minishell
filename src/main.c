/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:58:52 by jose              #+#    #+#             */
/*   Updated: 2023/05/25 15:55:50 by jose             ###   ########.fr       */
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

int	main(int ac, char **av, char **envp)
{
	char	*line;
	char	**env;

	(void)av;
	if (ac > 1)
		ft_error(BAD_PARAMETERS, "minishell : bad usage");
	signal(SIGINT, ft_sigint_handler);
	signal(SIGQUIT, ft_sigquit_handler);
	g_inf = malloc(sizeof(*g_inf)); //initialisation
	if (!g_inf)
		ft_error(MALLOC_FAILED, "g_inf : malloc failed");
	g_inf->exit_code = 0;
	g_inf->line = NULL;
	g_inf->top = NULL;
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
		/* ici les guillemets et variable de merde */
		g_inf->line = line;
		if(ft_is_builtin_no_pipe(line))
			ft_builtin_no_pipe(line, env);
		else
			ft_exec_manager(line, env);
		free(line);
	}
	return (ft_free_all(env), EXIT_SUCCESS);
}
