/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 08:17:32 by ahsalem           #+#    #+#             */
/*   Updated: 2023/01/05 17:02:12 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	fill_spheres(
	t_list **all_map_items, t_scene *scene)
{
	int		i;
	t_list	*tmp;
	int		occurance;

	i = 0;
	tmp = *all_map_items;
	occurance = count_occurance_in_map(all_map_items, "sp");
	scene->n_spheres = occurance;
	if (!occurance)
		return (0);
	scene->spheres = ft_calloc(sizeof(t_sphere), (occurance + 2));
	if (!scene->spheres)
		return (1);
	while (i < occurance)
	{
		tmp = get_next_occurance(tmp, "sp");
		tmp = tmp->next;
		fill_single_sphere(scene, tmp, i);
		scene->spheres[i].n_spheres = occurance;
		i++;
	}
	vis_spheres(scene);
	return (0);
}

int	fill_single_sphere(t_scene *scene, t_list *tmp, int i)
{
	if (vector_init(&scene->spheres[i].center, tmp))
		return (1);
	scene->spheres[i].diameter = ft_atof((char *)tmp->next->content);
	if (vector_init(&scene->spheres[i].color, tmp->next->next))
		return (1);
	return (0);
}

int	fill_planes(
	t_list **all_map_items, t_scene *scene)
{
	int		i;
	t_list	*tmp;
	int		occurance;

	i = 0;
	tmp = *all_map_items;
	occurance = count_occurance_in_map(all_map_items, "pl");
	scene->n_planes = occurance;
	if (!occurance)
		return (0);
	scene->plane = ft_calloc(sizeof(t_plane), (occurance + 2));
	if (!scene->plane)
		return (1);
	while (i < occurance)
	{
		tmp = get_next_occurance(tmp, "pl");
		tmp = tmp->next;
		fill_single_plane(scene, tmp, i);
		if (check_normalized_coord(scene->plane[i].orientation))
			return (1);
		scene->plane[i].n_planes = occurance;
		i++;
	}
	return (0);
}

int	fill_single_plane(t_scene *scene, t_list *tmp, int i)
{
	if (vector_init(&scene->plane[i].pos, tmp))
		return (1);
	if (vector_init(&scene->plane[i].orientation, tmp->next))
		return (1);
	if (vector_init(&scene->plane[i].color, tmp->next->next))
		return (1);
	return (0);
}

int	fill_cylinders(
	t_list **all_map_items, t_scene *scene)
{
	int		i;
	t_list	*tmp;
	int		occurance;

	i = 0;
	tmp = *all_map_items;
	occurance = count_occurance_in_map(all_map_items, "cy");
	scene->n_cylinders = occurance;
	if (!occurance)
		return (0);
	scene->cylinder = ft_calloc(sizeof(t_cylinder), (occurance + 2));
	if (!scene->cylinder)
		return (1);
	while (i < occurance)
	{
		tmp = get_next_occurance(tmp, "cy");
		tmp = tmp->next;
		fill_single_cylinder(scene, tmp, i);
		if (check_normalized_coord(scene->cylinder[i].orientation))
			return (1);
		scene->cylinder[i].n_cylinders = occurance;
		i++;
	}
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


//for all cokior