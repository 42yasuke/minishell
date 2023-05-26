/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdquote2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 22:45:33 by jose              #+#    #+#             */
/*   Updated: 2023/05/27 00:37:07 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	ft_replace_str_in_tab(char **tab, char *str, int *i)
{
	int		j;
	int		stop;
	char	*tmp;
	char	*tmp2;

	j = -1;
	if (!str)
		return ;
	stop = ft_nb_str(tab) + 1;
	while (++j < stop)
	{
		if (j == *i)
		{
			tmp = tab[j];
			tab[j] = str;
		}
		else if (j > *i)
		{
			tmp2 = tab[j];
			tab[j] = tmp;
			tmp = tmp2;
		}
	}
	*i = *i + 2;
}

static char	*ft_bf_str(char **tab, int i)
{
	char	*bf;
	int		j;
	int		is_d;

	j = -1;
	is_d = false;
	bf = ft_strdup(tab[i]);
	if (!bf)
		ft_error(MALLOC_FAILED, "bf : malloc failed");
	while (bf[++j])
	{
		if (bf[j] == '$')
		{
			if (!j)
				return (free(bf), NULL);
			is_d = true;
		}
		if (is_d)
			bf[j] = '\0';
	}
	return (bf);
}

static char	*ft_nenv_str(char **tab, int i, int *j2)
{
	char	*name_env;
	int		j;

	name_env = ft_strchr(tab[i], '$');
	name_env = ft_strdup(name_env);
	if (!name_env)
		ft_error(MALLOC_FAILED, "name_env : malloc failed");
	j = -1;
	*j2 = -1;
	while (name_env[++j])
	{
		if (*j2 == -1 && ft_is_whitespace(name_env[j]))
			*j2 = j;
		else if (*j2 != -1)
			name_env[j] = '\0';
	}
	return (name_env);
}

static char	*ft_af_str(char **tab, int i, int j2)
{
	char	*af;

	af = ft_strchr(tab[i], '$') + 1;
	af = ft_strdup(af);
	if (j2 != -1)
		af = ft_memmove(af, af + j2 + 1, ft_strlen(af + j2));
	else
	{
		free(af);
		af = NULL;
	}
	return (af);
}

void	ft_update_tab(char **tab, int i)
{
	char	*name_env;
	char	*bf;
	char	*af;
	int		j2;

	bf = ft_bf_str(tab, i);
	name_env = ft_nenv_str(tab, i, &j2);
	af = ft_af_str(tab, i, j2);
	free(tab[i]);
	tab[i] = name_env;
	ft_replace_str_in_tab(tab, bf, &i);
	ft_replace_str_in_tab(tab, af, &i);
}

char	*ft_merge_tab(char **tab)
{
	char	*line;
	int		nbr_char;
	int		i;
	int		j;
	

	i = -1;
	nbr_char = 0;
	while (tab[++i])
		nbr_char += ft_strlen(tab[i]);
	line = malloc(sizeof(*line) * (nbr_char + i));
	if (!line)
		ft_error(MALLOC_FAILED, "ft_merge_tab : line : malloc failed");
	nbr_char = -1;
	i = -1;
	while (tab[++i])
	{
		j = -1;
		while (tab[i][++j])
			line[++nbr_char] = tab[i][j];
		line[++nbr_char] = ' ';
	}
	return (line[nbr_char] = '\0', line);
}
