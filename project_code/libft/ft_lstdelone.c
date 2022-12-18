/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:10:00 by ayassin           #+#    #+#             */
/*   Updated: 2022/12/19 00:47:40 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* use "del" function on the content of node "lst"*/
void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst)
	{
		if (lst->content)
			del(lst->content);
		free(lst);
		lst = NULL;
	}
}

void	del(void *content)
{
	if (content)
	{
		free(content);
		content = NULL;
	}
}