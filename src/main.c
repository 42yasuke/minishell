/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jralph <jralph@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:58:52 by jose              #+#    #+#             */
/*   Updated: 2023/10/23 12:54:36 by jralph           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	g_exit_code = 0;

static void	ft_main_init_signal(int ac)
{
	rl_catch_signals = 0;
	if (ac > 1)
		ft_error(BAD_PARAMETERS, "parameters", "bad usage", NULL);
	ft_make_attention_these_signals();
}

static void	ft_main_suite(char *line, t_ginf *ginf)
{
	if (!ft_verif_line(line, true))
		return (free(line));
	ft_reset_ginf(ginf);
	line = ft_sd_quote_manager(line, ginf->env);
	ginf->line = line;
	if (!ft_verif_line(line, false))
		return (ft_free_ginf(ginf, false));
	if (line)
	{
		if (!ft_strchr(line, PIPE) && ft_is_builtin_no_pipe(line))
			ft_builtin_no_pipe(line, ginf);
		else
			ft_exec_manager(line, ginf);
	}
	ft_free_ginf(ginf, false);
}

int	main(int ac, char **av, char **envp)
{
	char			*line;
	static t_ginf	*ginf;

	(void)av;
	if (!isatty(STDIN_FILENO))
		ft_error(ERROR2, "minishell", "stdin is not a tty\n", NULL);
	ft_main_init_signal(ac);
	ginf = malloc(sizeof(*ginf));
	if (!ginf)
		ft_error(ERROR, "g_inf", "malloc failed", NULL);
	ft_init_ginf(ginf, envp);
	while (true)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (*line)
			(add_history(line), ft_main_suite(line, ginf));
		else
			free(line);
	}
	return (ft_printf("exit\n"), ft_free_ginf(ginf, true), g_exit_code);
}
