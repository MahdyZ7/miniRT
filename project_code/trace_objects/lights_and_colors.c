/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights_and_colors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 16:57:32 by ahsalem           #+#    #+#             */
/*   Updated: 2023/01/07 18:49:37 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

//figure out closest t from the plane and sphere then plot it
int	vec_to_color(t_vec vec)
{
	int	color;

	color = 0;
	if (vec.x >= 255)
		color += 255 << 16;
	else
		color += (int)(vec.x) << 16 ;
	if (vec.y >= 255)
		color += 255 << 8;
	else
		color += (int)(vec.y) << 8;
	if (vec.z >= 255)
		color += 255;
	else
		color += (int)(vec.z);
	return (color);
}

float	compute_color(t_vec *dir, t_sphere *sphr, t_scene *scene, float close_t)
{
	float	i;
	t_vec	normal;
	t_vec	hit_point;
	t_vec	light_vec;

	i = 0;
	hit_point = vec_scalar_mult(dir, close_t);
	hit_point = vec_add(&(scene->camera.view_point), &hit_point);
	normal = vec_sub(&hit_point, &(sphr->center));
	light_vec = vec_sub(&(scene->light.pos), &hit_point);
	i += scene->amb_light.ratio;
	if (vec_dot(&normal, &light_vec) > 0)
		i += scene->light.brightness * vec_dot(&normal, &light_vec)
			/ (vector_magnitude(&normal) * vector_magnitude(&light_vec));
	return (i);
}

t_vec	compute_color_to_vec(
			t_vec *dir, t_sphere *sphr, t_scene *scene, float close_t)
{
	t_vec	i;
	t_vec	normal;
	t_vec	hit_point;
	t_vec	light_vec;

	fill_single_vector(&i, 0, 0, 0);
	hit_point = vec_scalar_mult(dir, close_t);
	hit_point = vec_add(&(scene->camera.view_point), &hit_point);
	normal = vec_sub(&hit_point, &(sphr->center));
	light_vec = vec_sub(&(scene->light.pos), &hit_point);
	vec_scalar_add(&i, scene->amb_light.ratio);
	i.x += scene->amb_light.ratio * scene->amb_light.color.x;
	i.y += scene->amb_light.ratio * scene->amb_light.color.y;
	i.z += scene->amb_light.ratio * scene->amb_light.color.z;
	if (hit_other_object(hit_point, light_vec, scene))
		return (i);
	if (vec_dot(&normal, &light_vec) > 0)
		i = add_sphere_spot_light(scene, &normal, &light_vec, &i);
	return (i);
}

t_vec	add_sphere_spot_light(
	t_scene *scene, t_vec *normal, t_vec *light_vec, t_vec *i)
{
	i->x += scene->light.brightness * scene->light.color.x
		* vec_dot(normal, light_vec) / (vector_magnitude(normal)
			* vector_magnitude(light_vec));
	i->y += scene->light.brightness * scene->light.color.y
		* vec_dot(normal, light_vec) / (vector_magnitude(normal)
			* vector_magnitude(light_vec));
	i->z += scene->light.brightness * scene->light.color.z
		* vec_dot(normal, light_vec) / (vector_magnitude(normal)
			* vector_magnitude(light_vec));
	return (*i);
}

