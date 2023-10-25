/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jralph <jralph@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:50:44 by jose              #+#    #+#             */
/*   Updated: 2023/10/25 17:56:51 by jralph           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	ft_create_file_help(char *tmp_free, int red)
{
	char	*tmp;

	if (!tmp_free)
		ft_error(ERROR, "ft_create_file", "malloc failled", NULL);
	tmp = tmp_free;
	while (*tmp && (*tmp == red || *tmp == SPACE_TO_CUT))
		tmp++;
	ft_memmove(tmp_free, tmp, ft_strlen(tmp));
	tmp = tmp_free;
	while (*tmp && *tmp != SPACE_TO_CUT)
		tmp++;
	*tmp = '\0';
}

static void	ft_open_him(char *file_name, int red, int is_append)
{
	int		fd;

	if (red == REDIN)
		fd = open(file_name, O_RDONLY);
	else if (is_append)
		fd = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd != -1)
		close(fd);
	else
	{
		if (!access(file_name, F_OK))
			ft_error2(OPEN_FAILED, file_name, "Permission denied");
		else
			ft_error2(OPEN_FAILED, file_name, "No such file or directory");
	}
}

static void	ft_create_file(char *str, t_ginf *ginf, char *ret)
{
	char	*tmp_free;
	int		is_limiter;
	int		is_append;
	int		red;

	red = *str;
	is_limiter = (red == REDIN && *(str + 1) == red);
	is_append = (red == REDOUT && *(str + 1) == red);
	tmp_free = ft_strdup(str);
	ft_create_file_help(tmp_free, red);
	if (is_limiter)
		ft_here_doc(tmp_free, ginf->env);
	else
		ft_open_him(tmp_free, red, is_append);
	free(tmp_free);
	if (g_exit_code == OPEN_FAILED)
		free(ret);
}

static char	*ft_create_all_files(char *ret, int red, t_ginf *ginf)
{
	char	*tmp;
	char	*last_tmp;

	last_tmp = NULL;
	tmp = ft_get_next_redir(ret);
	while (tmp)
	{
		last_tmp = tmp;
		ft_create_file(tmp, ginf, ret);
		if (g_exit_code == OPEN_FAILED)
			return (NULL);
		tmp = ft_get_next_redir(tmp + 1);
		if (tmp - last_tmp == 1 && *tmp == *last_tmp)
			tmp = ft_get_next_redir(tmp + 1);
	}
	tmp = ft_strchr(ret, red);
	while (tmp)
	{
		last_tmp = tmp;
		tmp = ft_strchr(tmp + 1, red);
	}
	while (*last_tmp == REDIN || *last_tmp == REDOUT)
		last_tmp++;
	return (last_tmp);
}

char	*ft_give_fn(char *str, int red, t_ginf *ginf)
{
	char	*ret;
	char	*tmp;
	char	*last_tmp;

	if (g_exit_code == OPEN_FAILED)
		return (NULL);
	ret = ft_strdup(str);
	if (!ret)
		ft_error(ERROR, "ft_strdup", "malloc failed", NULL);
	last_tmp = ft_create_all_files(ret, red, ginf);
	if (!last_tmp)
		return (NULL);
	(ft_peek(&last_tmp), ft_memmove(ret, last_tmp, ft_strlen(last_tmp)));
	tmp = ret;
	while (*tmp && *tmp != SPACE_TO_CUT)
		tmp++;
	return (*tmp = '\0', ret);
}
