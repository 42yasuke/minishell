/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jralph <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:56:22 by jralph            #+#    #+#             */
/*   Updated: 2022/11/15 13:56:28 by jralph           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*nlst;
	t_list	*start;

	start = 0;
	while (lst)
	{
		nlst = ft_lstnew((*f)(lst->content));
		if (!nlst)
			ft_lstclear(&lst, del);
		ft_lstadd_back(&start, nlst);
		lst = lst->next;
	}
	return (start);
}
