/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 21:21:06 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/18 08:57:26 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_split(void **splited)
{
	int	i;

	i = 0;
	if (!splited)
		return ;
	while (splited[i])
	{
		if (splited[i])
			free(splited[i]);
		i++;
	}
	free(splited);
}
