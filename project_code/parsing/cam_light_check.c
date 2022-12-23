/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_light_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 23:05:05 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/23 15:58:49 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

//will nedd normilaztion for orientation vector
int	check_camera_data(t_list **all_map_items, t_scene *scene)
{
	int		occurance;
	t_list	*tmp;

	tmp = *all_map_items;
	occurance = count_occurance_in_map(all_map_items, "C");
	if (occurance != 1)
		return (1);
	tmp = get_next_occurance(tmp, "C");
	tmp = tmp->next;
	if (!check_there_is_next_elements(&tmp, 3))
		return (1);
	if (scan_camera_errors(tmp, occurance))
		return (1);
	(void)scene;
	return (0);
}

int	check_light_data(t_list **all_map_items, t_scene *scene)
{
	int		occurance;
	t_list	*tmp;

	tmp = *all_map_items;
	occurance = count_occurance_in_map(all_map_items, "L");
	if (occurance != 1)
		return (1);
	tmp = get_next_occurance(tmp, "L");
	tmp = tmp->next;
	if (!check_there_is_next_elements(&tmp, 3))
		return (1);
	if (scan_light_errors(tmp, occurance))
		return (1);
	(void)scene;
	return (0);
}

int	check_ambient_light_data(t_list **all_map_items, t_scene *scene)
{
	int		occurance;
	t_list	*tmp;

	tmp = *all_map_items;
	occurance = count_occurance_in_map(all_map_items, "A");
	if (occurance != 1)
		return (1);
	tmp = get_next_occurance(tmp, "A");
	tmp = tmp->next;
	if (!check_there_is_next_elements(&tmp, 2))
		return (1);
	if (scan_ambient_light_errors(tmp, occurance))
		return (1);
	(void) scene;
	return (0);
}