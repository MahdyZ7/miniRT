/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_plane_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 19:13:24 by ahsalem           #+#    #+#             */
/*   Updated: 2023/01/14 18:41:23 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_vec	compute_cylinder_color(t_scene *scene,
		t_vec *dir, t_cylinder *closest_cylinder, float close_t)
{
	t_compute_cy_color_kit	kit;

	init_compute_cy_color_kit(&kit);
	kit.hit_point = vec_scalar_mult(dir, close_t);
	kit.hit_point = vec_add(&(scene->camera.view_point), &kit.hit_point);
	kit.temp = vec_sub(&kit.hit_point, &(closest_cylinder->pos));
	kit.t = vec_dot(&kit.temp, &(closest_cylinder->orientation));
	kit.temp = vec_scalar_mult(&(closest_cylinder->orientation), kit.t);
	kit.temp = vec_add(&kit.temp, &(closest_cylinder->pos));
	kit.normal = vec_sub(&kit.hit_point, &kit.temp);
	normalize(&kit.normal);
	kit.light_vec = vec_sub(&(scene->light.pos), &kit.hit_point);
	kit.i.x += scene->amb_light.ratio * scene->amb_light.color.x;
	kit.i.y += scene->amb_light.ratio * scene->amb_light.color.y;
	kit.i.z += scene->amb_light.ratio * scene->amb_light.color.z;
	if (hit_other_object(kit.hit_point, kit.light_vec, scene))
		return (kit.i);
	if (vec_dot(&kit.normal, &kit.light_vec) > 0)
		kit.i = add_sphere_spot_light(
				scene, &kit.normal, &kit.light_vec, &kit.i);
	return (kit.i);
}

void	init_compute_cy_color_kit(t_compute_cy_color_kit *kit)
{
	ft_bzero((void *)kit, sizeof(t_compute_cy_color_kit));
	fill_single_vector(&kit->i, 0, 0, 0);
}

t_vec	plane_color(t_vec *dir, t_plane *pln, t_scene *scene, float close_t)
{
	t_vec	i;
	t_vec	normal;
	t_vec	hit_point;
	t_vec	light_vec;
	float	a;

	fill_single_vector(&i, 0, 0, 0);
	hit_point = vec_scalar_mult(dir, close_t);
	hit_point = vec_add(&(scene->camera.view_point), &hit_point);
	normal = pln->orientation;
	light_vec = vec_sub(&(scene->light.pos), &hit_point);
	i.x += scene->amb_light.ratio * scene->amb_light.color.x;
	i.y += scene->amb_light.ratio * scene->amb_light.color.y;
	i.z += scene->amb_light.ratio * scene->amb_light.color.z;
	if (hit_other_object(hit_point, light_vec, scene))
		return (i);
	a = ((vec_dot(&normal, &light_vec)));
	if (a < 0)
	{
		i = add_plane_spot_light(scene, &normal, &light_vec, &i);
	}
	return (i);
}

t_vec	add_plane_spot_light(
	t_scene *scene, t_vec *normal, t_vec *light_vec, t_vec *i)
{
	float	a;

	a = fabsf(vec_dot(normal, light_vec));
	i->x += scene->light.brightness * scene->light.color.x
		* a / (vector_magnitude(normal) * vector_magnitude(light_vec));
	i->y += scene->light.brightness * scene->light.color.y
		* a / (vector_magnitude(normal) * vector_magnitude(light_vec));
	i->z += scene->light.brightness * scene->light.color.z
		* a / (vector_magnitude(normal) * vector_magnitude(light_vec));
	return (*i);
}
