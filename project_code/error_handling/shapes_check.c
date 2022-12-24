/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 16:11:02 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/24 09:34:13 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	scan_sphere_errors(t_list *tmp)
{
	printf("\nscanning sphere\n");
	if (check_coordinates_error(tmp)
		|| !ft_is_float((char *)tmp->next->content)
		|| check_coordinate_range(tmp->next->next)
		)
	{
		return (1);
	}
	if (!tmp->next->next->next)
		return (0);
	if (!ft_the_strcmp((char *)tmp->next->next->next->content, "\n"))
			return (0);
	return (1);
}

int	scan_plane_errors(t_list *tmp)
{
	printf("\nscanning plane\n");
	if (check_coordinates_error(tmp)
		|| check_coordinates_error(tmp->next)
		|| check_coordinate_range(tmp->next->next))
	{
		return (1);
	}
	if (!tmp->next->next->next)
		return (0);
	if (!ft_the_strcmp((char *)tmp->next->next->next->content, "\n"))
			return (0);
	return (1);
}

int	scan_cylender_errors(t_list *tmp)
{
	printf("\nscanning Cylinder\n");
	if (check_coordinates_error(tmp)
		|| check_coordinates_error(tmp->next)
		|| !ft_is_float((char *)tmp->next->next->content)
		|| !ft_is_float((char *)tmp->next->next->next->content)
		|| check_coordinate_range(tmp->next->next->next->next)
		)
	{
		return (1);
	}
	if (!tmp->next->next->next->next->next)
		return (0);
	if (!ft_the_strcmp((char *)tmp->next->next->next->next->next->content, "\n"))
			return (0);
	return (1);
}
