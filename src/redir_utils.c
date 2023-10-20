/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jralph <jralph@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:50:44 by jose              #+#    #+#             */
/*   Updated: 2023/10/20 17:07:43 by jralph           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static char	*ft_give_fn_a_src(char *str, int red)
{
	char	*src;

	src = str;
	while (*src == red)
		src++;
	ft_peek(&src);
	while (*src && !ft_is_whitespace(*src) && *src != SPACE_TO_CUT)
		src++;
	return (src);
}

void	ft_make_me_point_on_cmd(char *str, int red)
{
	char	*src;
	char	*tmp;

	tmp = ft_strchr(str, red);
	while (tmp)
	{
		src = ft_give_fn_a_src(tmp, red);
		ft_memmove(tmp, src, ft_strlen(src));
		tmp = ft_strchr(str, red);
	}
	while (ft_is_whitespace(*str) || *str == SPACE_TO_CUT)
		ft_memmove(str, str + 1, ft_strlen(str + 1));
}

static void	ft_open_him(char *file_name, int red)
{
	int		fd;

	if (red == REDIN)
		fd = open(file_name, O_RDONLY);
	else
		fd = open(file_name, O_CREAT | O_WRONLY, 0644);
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

static void	ft_create_file(char *str, int red, t_ginf *ginf, char *ret)
{
	char	*tmp;
	char	*tmp_free;
	int		is_limiter;

	if (*(str + 1) == red)
		return ;
	is_limiter = (red == REDIN && str != ret && *(str - 1) == red);
	tmp_free = ft_strdup(str);
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
	if (is_limiter)
		ft_here_doc(tmp_free, ginf->env);
	else
		ft_open_him(tmp_free, red);
	free(tmp_free);
	if (g_exit_code == OPEN_FAILED)
		free(ret);
}

char	*ft_give_fn(char *str, int red, t_ginf *ginf, t_cmd **cmd)
{
	char	*ret;
	char	*tmp;
	char	*last_tmp;

	ret = ft_strdup(str);
	if (!ret)
		ft_error(ERROR, "ft_strdup", "malloc failed", NULL);
	last_tmp = NULL;
	tmp = ft_strchr(ret, red);
	while (tmp)
	{
		last_tmp = tmp;
		ft_create_file(tmp, red, ginf, ret);
		if (g_exit_code == OPEN_FAILED)
			(ft_free_cmd(*cmd, NULL), \
			ft_free_ginf(ginf, true, *cmd), exit(EXIT_FAILURE));
		tmp = ft_strchr(tmp + 1, red);
	}
	last_tmp++;
	ft_peek(&last_tmp);
	ft_memmove(ret, last_tmp, ft_strlen(last_tmp));
	tmp = ret;
	while (*tmp && *tmp != SPACE_TO_CUT)
		tmp++;
	return (*tmp = '\0', ret);
}
