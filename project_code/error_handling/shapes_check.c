/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 16:11:02 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/23 16:22:11 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	scan_sphere_errors(t_list *tmp)
{
	printf("\nscanning sphere\n");
	if (check_coordinates_error(tmp)
		|| !ft_is_float((char *)tmp->next->content)
		|| check_coordinate_range(tmp->next->next)
		|| ft_the_strcmp((char *)tmp->next->next->next->content, "\n"))
	{
		return (1);
	}
	return (0);
}
