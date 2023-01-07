/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 08:17:26 by ahsalem           #+#    #+#             */
/*   Updated: 2023/01/07 18:32:39 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	fill_all_elements_in_scene(t_list **all_map_items, t_scene *scene)
{
	if (fill_ambient_light(all_map_items, scene)
		|| fill_light(all_map_items, scene)
		|| fill_camera(all_map_items, scene)
		|| fill_spheres(all_map_items, scene)
		|| fill_planes(all_map_items, scene)
		|| fill_cylinders(all_map_items, scene))
		return (1);
	return (0);
}

int	fill_single_cylinder(t_scene *scene, t_list *tmp, int i)
{
	if (vector_init(&scene->cylinder[i].pos, tmp))
		return (1);
	if (vector_init(&scene->cylinder[i].orientation, tmp->next))
		return (1);
	scene->cylinder[i].diameter = ft_atof((char *)tmp->next->next->content);
	scene->cylinder[i].height = ft_atof((char *)tmp->next->next->next->content);
	if (vector_init(&scene->cylinder[i].color, tmp->next->next->next->next))
		return (1);
	return (0);
}

t_list	*fill_line_node(char *arg, char type)
{
	t_list	*new_node;

	new_node = ft_lstnew(NULL);
	new_node->content = (void *)arg;
	new_node->type = type;
	return (new_node);
}
