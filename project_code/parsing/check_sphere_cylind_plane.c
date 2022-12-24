/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sphere_cylind_plane.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 15:11:24 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/24 06:32:31 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	check_sphere(t_list **all_map_items, t_scene *scene)
{
	int		occurance;
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = *all_map_items;
	occurance = count_occurance_in_map(all_map_items, "sp");
	scene->number_of_shapes += occurance;
	if (!occurance)
		return (0);
	while (i < occurance)
	{
		tmp = get_next_occurance(tmp, "sp");
		tmp = tmp->next;
		if (!check_there_is_next_elements(&tmp, 2))
			return (1);
		if (scan_sphere_errors(tmp))
			return (1);
		i++;
	}
	return (0);
}

int	check_cylender(t_list **all_map_items, t_scene *scene)
{
	int		occurance;
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = *all_map_items;
	occurance = count_occurance_in_map(all_map_items, "cy");
	scene->number_of_shapes += occurance;
	if (!occurance)
		return (0);
	while (i < occurance)
	{
		tmp = get_next_occurance(tmp, "cy");
		tmp = tmp->next;
		if (!check_there_is_next_elements(&tmp, 3))
			return (1);
		if (scan_cylender_errors(tmp))
			return (1);
		i++;
	}
	return (0);
}

int	check_plane(t_list **all_map_items, t_scene *scene)
{
	int		occurance;
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = *all_map_items;
	occurance = count_occurance_in_map(all_map_items, "pl");
	scene->number_of_shapes += occurance;
	if (!occurance)
		return (0);
	while (i < occurance)
	{
		tmp = get_next_occurance(tmp, "pl");
		tmp = tmp->next;
		if (!check_there_is_next_elements(&tmp, 2))
			return (1);
		if (scan_plane_errors(tmp))
			return (1);
		i++;
	}
	return (0);
}
