/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_elements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 08:17:10 by ahsalem           #+#    #+#             */
/*   Updated: 2023/01/05 16:45:57 by ahsalem          ###   ########.fr       */
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
	if (check_normalized_coord(scene->camera.orientation))
		return (1);
	scene->camera.view_field = ft_atof((char *)tmp->next->next->content);
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
	vec_init(&(sphere->color), color >> 16, (color >> 8) & 0xff, color & 0xff);
}
