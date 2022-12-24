/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 16:12:46 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/24 14:00:00 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

//check for the end of line and the new line
int	scan_camera_errors(t_list *tmp, int occurance)
{
	printf("\nscanning camera\n");
	if (occurance > 1 || check_coordinates_error(tmp)
		|| check_coordinates_error(tmp->next)
		|| check_int_range(tmp->next->next, 0, 180)
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

int	scan_light_errors(t_list *tmp, int occurance)
{
	printf("\nscanning light\n");
	if (occurance > 1 || check_coordinates_error(tmp)
		|| check_float_range(tmp->next, 0.0, 1.1)
		|| check_coordinate_range(tmp->next->next)
		|| ft_the_strcmp((char *)tmp->next->next->next->content, "\n"))
	{
		return (1);
	}
	if (!tmp->next->next->next)
		return (0);
	if (!ft_the_strcmp((char *)tmp->next->next->next->content, "\n"))
		return (0);
	return (1);
}

int	scan_ambient_light_errors(t_list *tmp, int occurance)
{
	printf("\nchecking Ambient light \n");
	if (occurance > 1 || check_float_range(tmp, 0.0, 1.1)
		|| check_coordinate_range(tmp->next))
	{
		return (1);
	}
	if (!tmp->next->next)
		return (0);
	if (!ft_the_strcmp((char *)tmp->next->next->content, "\n"))
		return (0);
	return (1);
}

int	not_valid_element(t_list *check_me)
{
	int			i;
	static char	*valid_element[8] = {
		"A", "C", "L", "sp", "pl", "cy", "sp", "\n"
	};

	i = 0;
	while (i < 8)
	{
		if (!ft_the_strcmp((char *)check_me->content, valid_element[i]))
			return (0);
		i++;
	}
	return (1);
}
