/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 16:12:46 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/23 16:21:53 by ahsalem          ###   ########.fr       */
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
		|| ft_the_strcmp((char *)tmp->next->next->next->content, "\n"))
		return (1);
	else
		return (0);
}

int	scan_light_errors(t_list *tmp, int occurance)
{
	printf("\nscanning light\n");
	if (occurance > 1 || check_coordinates_error(tmp)
		|| check_float_range(tmp->next, 0.0, 1.1)
		|| check_coordinate_range(tmp->next->next)
		|| ft_the_strcmp((char *)tmp->next->next->next->content, "\n"))
		return (1);
	else
		return (0);
}

int	scan_ambient_light_errors(t_list *tmp, int occurance)
{
	printf("\nchecking Ambient light \n");
	if (occurance > 1 || check_float_range(tmp, 0.0, 1.1)
		|| check_coordinate_range(tmp->next)
		|| ft_the_strcmp((char *)tmp->next->next->content, "\n"))
		return (1);
	else
		return (0);
}
