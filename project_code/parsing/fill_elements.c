/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_elements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 08:17:10 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/24 14:26:22 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	fill_ambient_light(
	t_list **all_map_items, t_scene *scene)
{
	t_list	*tmp;

	tmp = *all_map_items;
	tmp = get_next_occurance(tmp, "A");
	tmp = tmp->next;
	scene->amb_light.ratio = ft_atof((char *)tmp->content);
	if (vector_init(&scene->amb_light.color, tmp->next))
		return (1);
	return (0);
}

int	fill_light(
	t_list **all_map_items, t_scene *scene)
{
	t_list	*tmp;

	tmp = *all_map_items;
	tmp = get_next_occurance(tmp, "L");
	tmp = tmp->next;
	if (vector_init(&scene->light.pos, tmp))
		return (1);
	scene->light.brightness = ft_atof((char *)tmp->next->content);
	if (vector_init(&scene->light.color, tmp->next->next))
		return (1);
	return (0);
}

int	fill_camera(
	t_list **all_map_items, t_scene *scene)
{
	t_list	*tmp;

	tmp = *all_map_items;
	tmp = get_next_occurance(tmp, "C");
	tmp = tmp->next;
	if (vector_init(&scene->camera.view_point, tmp))
		return (1);
	if (vector_init(&scene->camera.orientation, tmp->next))
		return (1);
	scene->camera.view_field = ft_atof((char *)tmp->next->next->content);
	return (0);
}

int	fill_spheres(
	t_list **all_map_items, t_scene *scene)
{
	int		i;
	t_list	*tmp;
	int		occurance;

	i = 0;
	tmp = *all_map_items;
	occurance = count_occurance_in_map(all_map_items, "sp");
	if (!occurance)
		return (0);
	scene->spheres = malloc(sizeof(t_sphere) * occurance + 1);
	if (!scene->spheres)
		return (1);
	while (i < occurance)
	{
		tmp = get_next_occurance(tmp, "sp");
		tmp = tmp->next;
		fill_single_sphere(scene, tmp, i);
		scene->spheres[i].last_sphere = 0;
		i++;
	}
	scene->spheres[i].last_sphere = 1;
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

void	vec_init(t_vec *vec, float x, float y, float z)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;
}

void	sphere_init(t_sphere *sphere, float x, float y, float z, float diameter, int color)
{
	vec_init(&(sphere->center), x, y, z);
	sphere->diameter = diameter;
	(void)color;
}
