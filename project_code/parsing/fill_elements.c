/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_elements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 08:17:10 by ahsalem           #+#    #+#             */
/*   Updated: 2023/01/11 19:43:51 by ahsalem          ###   ########.fr       */
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
	scene->amb_light.color = vec_scalar_mult(&scene->amb_light.color,
			1 / 255.0);
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
	scene->light.color = vec_scalar_mult(&scene->light.color, 1 / 255.0);
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
	if (scene->camera.orientation.z == 1)
		scene->camera.orientation.z = 0;
	if (scene->camera.orientation.z == -1)
		scene->camera.orientation.y = 3.15;
	// scene->camera.xyz_angles.x = (float)((int)scene->camera.xyz_angles.x % 180) * M_PI / 180;
	// scene->camera.xyz_angles.y = (float)((int)scene->camera.xyz_angles.y % 180) * M_PI / 180;
	// scene->camera.xyz_angles.z = (float)((int)scene->camera.xyz_angles.z % 180) * M_PI / 180;
	scene->camera.xyz_angles.x = scene->camera.orientation.y * -1;
	scene->camera.xyz_angles.y = scene->camera.orientation.x;
	scene->camera.xyz_angles.z = 0.0;
	// scene->camera.xyz_angles.z = (float)((int)(scene->camera.orientation.z * 1000) % 350) / 1000;
	// scene->camera.xyz_angles.x = scene->camera.orientation.x * M_PI;
	// scene->camera.xyz_angles.y = scene->camera.orientation.y * M_PI;
	// scene->camera.xyz_angles.z = scene->camera.orientation.z * M_PI;
	return (0);
}

void	vec_init(t_vec *vec, float x, float y, float z)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;
}

void	fill_calculated_vars(t_cylinder *cylinder, t_scene *scene)
{
	t_vec	cylinder_end;
	t_vec	vec_cylinder_height;
	t_vec	origin_to_cylinder;

	cylinder_end = get_cylinder_height(cylinder);
	vec_cylinder_height = vec_sub(&cylinder_end, &(cylinder->pos));
	origin_to_cylinder = vec_sub(&scene->camera.view_point, &(cylinder->pos));
	normalize(&vec_cylinder_height);
	cylinder->pos_top = get_cylinder_height(cylinder);
	cylinder->vec_height = vec_sub(&cylinder_end, &(cylinder->pos));
	cylinder->in_cylinder = vec_dot(&vec_cylinder_height, &origin_to_cylinder);
}