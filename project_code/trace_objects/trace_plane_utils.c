/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_plane_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 19:13:24 by ahsalem           #+#    #+#             */
/*   Updated: 2023/01/13 19:40:21 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"
//do the same changes as sphere
/*
	// old_hit = vec_scalar_mult(dir, close_t);
	// old_hit = vec_add(&(scene->camera.view_point), &hit_point);
	subtraction other option
	// light_vec = vec_sub(&hit_point, &(scene->light.pos));
	float a other option
	// float a= vec_dot(&normal, &light_vec);
	// normalize(&light_vec);
*/
t_vec	compute_cylinder_color(t_scene *scene, t_vec *dir,t_cylinder *closest_cylinder, float close_t)
{
	t_vec	i;
	t_vec	normal;
	t_vec	hit_point;
	t_vec	light_vec;

	fill_single_vector(&i, 0, 0, 0);
	hit_point = vec_scalar_mult(dir, close_t);
	hit_point = vec_add(&(scene->camera.view_point), &hit_point);
	t_vec temp = vec_sub(&hit_point, &(closest_cylinder->pos));
	double t = vec_dot(&temp, &(closest_cylinder->orientation)); // cy.ori should be normalized and so has the length of 1.
    temp = vec_scalar_mult(&(closest_cylinder->orientation), t);
	temp = vec_add(&temp, &(closest_cylinder->pos));
	// pt = cy.bottom_center + t * cy.ori;
	normal = vec_sub(&hit_point, &temp);
	normalize(&normal);
    // surface_normal = normalize(hit_point - pt)));
	light_vec = vec_sub(&(scene->light.pos), &hit_point);
	// normalize(&light_vec);
	i.x += scene->amb_light.ratio * scene->amb_light.color.x;
	i.y += scene->amb_light.ratio * scene->amb_light.color.y;
	i.z += scene->amb_light.ratio * scene->amb_light.color.z;
	if (hit_other_object(hit_point, light_vec, scene))
		return (i);
	// // vis_vector(normal);
	// // printf("\n");
	if (vec_dot(&normal, &light_vec) > 0)
	{
		// printf("ASASASAS");
		i = add_sphere_spot_light(scene, &normal, &light_vec, &i);
		// printf("i is %f %f %f\n" , i.x, i.y, i.z);
	}
	return (i);
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
