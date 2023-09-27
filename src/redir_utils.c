/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:50:44 by jose              #+#    #+#             */
/*   Updated: 2023/09/27 02:10:06 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static char	*ft_give_me_a_src(char *str, int red)
{
	char	*src;

	src = str;
	while (*src == red)
		src++;
	ft_peek(&src);
	while (*src && !ft_is_whitespace(*src))
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
		src = ft_give_me_a_src(tmp, red);
		ft_memmove(tmp, src, ft_strlen(src));
		tmp = ft_strchr(str, red);
	}
	while (ft_is_whitespace(*str))
		ft_memmove(str, str + 1, ft_strlen(str + 1));
}

static void	ft_create_file(char *str, int red)
{
	char	*tmp;
	char	*tmp_free;
	int		fd;

	if (red == REDIN)
		return ;
	if (*(str + 1) == red)
		return ;
	tmp_free = ft_strdup(str);
	if (!tmp_free)
		ft_error(MALLOC_FAILED, "ft_create_file", "malloc failled");
	tmp = tmp_free;
	while (*tmp && (*tmp == red || ft_is_whitespace(*tmp)))
		tmp++;
	ft_memmove(tmp_free, tmp, ft_strlen(tmp));
	while (*tmp && !ft_is_whitespace(*tmp))
		tmp++;
	*tmp = '\0';
	fd = open(tmp_free, O_CREAT, 0644);
	if (fd != -1)
		close(fd);
	free(tmp_free);
}

char	*ft_give_me_file_name(char *str, int red)
{
	char	*ret;
	char	*tmp;
	char	*last_tmp;

	ret = ft_strdup(str);
	if (!ret)
		ft_error(MALLOC_FAILED, "ft_strdup", "malloc failed");
	last_tmp = NULL;
	tmp = ft_strchr(ret, red);
	while (tmp)
	{
		last_tmp = tmp;
		ft_create_file(tmp, red);
		tmp = ft_strchr(tmp + 1, red);
	}
	last_tmp++;
	ft_peek(&last_tmp);
	ft_memmove(ret, last_tmp, ft_strlen(last_tmp));
	tmp = ret;
	while (*tmp && !ft_is_whitespace(*tmp))
		tmp++;
	return (*tmp = '\0', ret);
}

int	ft_is_it_a_double_red(char *str, int red)
{
	char	*tmp;
	char	*last_tmp;

	last_tmp = NULL;
	tmp = ft_strchr(str, red);
	while (tmp)
	{
		last_tmp = tmp;
		tmp = ft_strchr(tmp + 1, red);
	}
	if (last_tmp != str && *(last_tmp - 1) == red)
		return (true);
	return (false);
}
