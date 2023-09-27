/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jralph <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 23:51:56 by jralph            #+#    #+#             */
/*   Updated: 2022/11/14 23:51:59 by jralph           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*old;

	if (lst)
	{
		if (*lst)
		{
			old = ft_lstlast(*lst);
			old->next = new;
		}
		else
			*lst = new;
	}
}
