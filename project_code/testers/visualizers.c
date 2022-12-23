/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 15:22:02 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/19 00:28:01 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	vis_list(t_list **head)
{
	t_list	*tmp;
	int		i;

	i = 0;
	if (!head)
		return ;
	if (!*head)
		return ;
	tmp = *head;
	while (tmp)
	{
		ft_printf("%s~", tmp->content);
		tmp = tmp->next;
		i++;
	}
}
