/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jralph <jralph@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 12:28:41 by jose              #+#    #+#             */
/*   Updated: 2023/10/14 23:48:32 by jralph           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	ft_check_var_denv(char **ps, char **env)
{
	char	*tmp;

	ft_find_dollar_n_replace_it(*ps);
	tmp = *ps;
	*ps = ft_find_n_replace_var(*ps, env);
	free(tmp);
}

static void	ft_no_use_limitter(char *limiter, int tmp_stdin)
{
	char	*str_err;
	char	*tmp;

	str_err = "\nmini: warning: here-document delimited by EOF (wanted \'";
	str_err = ft_strjoin(str_err, limiter);
	tmp = str_err;
	str_err = ft_strjoin(str_err, "\')\n");
	if (g_exit_code != HD_SIGINT)
		write(STDERR_FILENO, str_err, ft_strlen(str_err));
	else
		write(STDERR_FILENO, "\n", 1);
	if (g_exit_code == HD_SIGINT && tmp_stdin != -1)
		(dup2(tmp_stdin, STDIN_FILENO), close(tmp_stdin));
	(free(str_err), free(tmp));
}

static int	ft_open_it_goodly(char *file_name)
{
	int		fd_ret;

	fd_ret = open(file_name, O_CREAT | O_WRONLY | O_APPEND | O_EXCL, 0644);
	if (fd_ret == -1)
	{
		unlink(file_name);
		fd_ret = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	}
	return (fd_ret);
}

void	ft_here_we_go(char *limiter, char *file_name, int tmp_stdin, char **env)
{
	int		fd_ret;
	char	*line;

	fd_ret = ft_open_it_goodly(file_name);
	write (STDOUT_FILENO, ">", 1);
	line = get_next_line(STDIN_FILENO);
	while (line && !(ft_strlen(line) == ft_strlen(limiter) + 1 && \
	!ft_strncmp(line, limiter, ft_strlen(limiter))) && g_exit_code != HD_SIGINT)
	{
		ft_check_var_denv(&line, env);
		(write (fd_ret, line, ft_strlen(line)), free(line));
		write (STDOUT_FILENO, ">", 1);
		line = get_next_line(STDIN_FILENO);
	}
	if (ft_strncmp(line, limiter, ft_strlen(limiter)))
		ft_no_use_limitter(limiter, tmp_stdin);
	if (line)
		(get_next_line(-10), free(line));
	close(fd_ret);
}

void	ft_here_doc(char *limiter, char **env)
{
	int		tmp_stdin;
	int		tmp_save;

	if (g_exit_code == HD_SIGINT)
		return ;
	tmp_stdin = dup(STDIN_FILENO);
	tmp_save = g_exit_code;
	g_exit_code = HERE_DOC;
	ft_here_we_go(limiter, "/tmp/.h_d", tmp_stdin, env);
	if (g_exit_code != HD_SIGINT)
	{
		g_exit_code = tmp_save;
		close(tmp_stdin);
	}
}
