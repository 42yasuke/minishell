/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 12:28:41 by jose              #+#    #+#             */
/*   Updated: 2023/09/27 01:14:04 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	ft_check_var_denv(char **ps)
{
	char	*tmp;

	ft_find_dollar_n_replace_it(*ps);
	tmp = *ps;
	*ps = ft_find_n_replace_var(*ps);
	free(tmp);
}

static void	ft_no_use_limitter(char *limiter)
{
	char	*str_err;
	char	*tmp;

	str_err = "\nmini: warning: here-document delimited by EOF (wanted \'";
	str_err = ft_strjoin(str_err, limiter);
	tmp = str_err;
	str_err = ft_strjoin(str_err, "\')\n");
	if (!g_inf->here_doc_quit)
		write(STDERR_FILENO, str_err, ft_strlen(str_err));
	else if (g_inf->tmp_stdin != -1)
		(dup2(g_inf->tmp_stdin, STDIN_FILENO), close(g_inf->tmp_stdin));
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

static void	ft_here_we_go(char *limiter, char *file_name)
{
	int		fd_ret;
	char	*line;

	g_inf->here_doc = true;
	fd_ret = ft_open_it_goodly(file_name);
	write (STDOUT_FILENO, ">", 1);
	line = get_next_line(STDIN_FILENO);
	while (line && !(ft_strlen(line) == ft_strlen(limiter) + 1 && \
	!ft_strncmp(line, limiter, ft_strlen(limiter))) && !g_inf->here_doc_quit)
	{
		ft_check_var_denv(&line);
		(write (fd_ret, line, ft_strlen(line)), free(line));
		write (STDOUT_FILENO, ">", 1);
		line = get_next_line(STDIN_FILENO);
	}
	if (ft_strncmp(line, limiter, ft_strlen(limiter)))
		ft_no_use_limitter(limiter);
	if (line)
		(get_next_line(-10), free(line));
	close(fd_ret);
}

void	ft_here_doc(t_cmd **cmd, char **ps)
{
	char	*limiter;
	char	*file;

	file = ft_strdup("/tmp/.h_d");
	if (!file)
		ft_error(MALLOC_FAILED, "ft_strdup", "malloc failled");
	limiter = ft_give_me_file_name(*ps, REDIN);
	ft_here_we_go(limiter, file);
	*cmd = ft_redircmd(*cmd, file, O_RDONLY, STDIN_FILENO);
	ft_make_me_point_on_cmd(*ps, REDIN);
	free(limiter);
}
