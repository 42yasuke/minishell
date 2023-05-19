/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jralph <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:25:09 by jralph            #+#    #+#             */
/*   Updated: 2022/11/15 12:25:13 by jralph           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*tmp2;

	if (lst)
	{
		if (*lst)
		{
			tmp = *lst;
			while (tmp)
			{
				(*del)(tmp->content);
				tmp2 = tmp->next;
				free(tmp);
				tmp = tmp2;
			}
		}
		*lst = NULL;
	}
}
