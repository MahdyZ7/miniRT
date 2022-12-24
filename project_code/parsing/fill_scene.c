/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 08:17:26 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/24 11:35:47 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	fill_all_elements_in_scene(t_list **all_map_items, t_scene *scene)
{
	if (fill_ambient_light(all_map_items, scene)
		|| fill_light(all_map_items, scene)
		|| fill_camera(all_map_items, scene)
		|| fill_spheres(all_map_items, scene))
		return (1);
	return (0);
}