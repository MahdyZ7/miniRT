/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_tracing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 11:37:30 by ayassin           #+#    #+#             */
/*   Updated: 2023/01/12 12:15:03 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

float	his_hit_cylinder(t_cylinder *cylinder, t_vec *origin, t_vec *dir, float t_min)
{
	t_vec	origin_to_cylinder;
	float	height_by_direction;
	float	a;
	float 	b;
	float	c;
	float	discriminant;
	float	t1;
	float	t2;
	t_vec 	temp_vec;
	t_vec 	limit_1;
	float	h_limit_1;
	t_vec 	limit_2;
	float	h_limit_2;

	(void)t_min;
	origin_to_cylinder = vec_sub(origin, &(cylinder->pos));
	normalize(&cylinder->vec_height);
	// float	height_dot_product = vec_dot(&cylinder->vec_height, &cylinder->vec_height);
	height_by_direction = vec_dot(&cylinder->vec_height, dir);
	cylinder->in_cylinder = vec_dot(&cylinder->vec_height, &origin_to_cylinder);
	a =  vec_dot(dir, dir) - height_by_direction * height_by_direction;
	b = 2 * (vec_dot(dir, &origin_to_cylinder) - height_by_direction * cylinder->in_cylinder);
	c = vec_dot(&origin_to_cylinder, &origin_to_cylinder) - cylinder->in_cylinder * cylinder->in_cylinder - cylinder->radius_square;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return INFINITY;
	t1 = (-b - sqrt(discriminant)) / (2 * a);
	t2 = (-b + sqrt(discriminant)) / (2 * a);
	if (t1 < t_min && t2 < t_min)
		return INFINITY;
	temp_vec = vec_scalar_mult(dir, t1);
	limit_1 = vec_add(&origin_to_cylinder, &temp_vec);
	h_limit_1 = vec_dot(&cylinder->vec_height, &limit_1);
	temp_vec = vec_scalar_mult(dir, t2);
	limit_2 = vec_add(&origin_to_cylinder, &temp_vec);
	h_limit_2 = vec_dot(&cylinder->vec_height, &limit_2);
	if (t1 < t_min && h_limit_2 > 0 && h_limit_2 < cylinder->height)
		return t2;
	if ((t2 < t_min || t1 < t2) && h_limit_1 > 0 && h_limit_1 < cylinder->height)
		return t1;
	if (h_limit_2 > 0 && h_limit_2 < cylinder->height)
		return (t2);
	return (INFINITY);
	
}

float	check_capped_part(float t0, float t1,
	 t_vec *origin, t_vec *dir, t_cylinder *cylinder)
{
	t_vec	result;
	t_vec	scaled_dir;

  if (t0 > 0) 
  {
	scaled_dir = vec_scalar_mult(dir, t0);
    result = vec_add(origin, &scaled_dir);
    if (result.y >= 0 && result.y <= cylinder->height)
      return (t0);
  }
  if (t1 > 0) 
  {
    scaled_dir = vec_scalar_mult(dir, t1);
    result = vec_add(origin, &scaled_dir);
    if (result.y >= 0 && result.y <= cylinder->height)
	{
      return (t1);
    }
  }
	return (INFINITY);
}

t_vec	trace_cylinder(t_vec *dir, float t_min, t_scene *scene)
{
	int			color;
	float		closest_t;
	float		temp_t;
	t_cylinder	*closest_cylinder;
	t_vec		result;

	closest_t = INFINITY;
	closest_cylinder = NULL;
	for (int i = 0; i < scene->n_cylinders; i++)
	{
		// temp_t = (hit_cylinder(&(scene->cylinder[i]), &scene->camera.view_point, dir, t_min)).t;
		temp_t = his_hit_cylinder(&(scene->cylinder[i]), &scene->camera.view_point, dir, t_min);
		if (temp_t < closest_t)
		{
			closest_t = temp_t;
			closest_cylinder = &(scene->cylinder[i]);
		}
	}
	color = 0x000000;
	if (closest_cylinder != NULL)
	{
		t_vec m = compute_cylinder_color(scene, dir, closest_cylinder, closest_t);
		t_vec cyl_color = vec_multiply_two_vectors(&(closest_cylinder->color), &m);
		color  = vec_to_color(cyl_color);
		// vis_vector(cyl_color);
		// printf("\n");
	}
	fill_single_vector(&result, closest_t, color, 0);
	return (result);
}

t_vec	get_cylinder_height(t_cylinder *cylinder)
{
	t_vec	result;

	result.x = cylinder->pos.x + cylinder->orientation.x * cylinder->height;
	result.y = cylinder->pos.y + cylinder->orientation.y * cylinder->height;
	result.z = cylinder->pos.z + cylinder->orientation.z * cylinder->height;
	return (result);
}
/* old code
float	hit_cylinder(t_cylinder *cylinder, t_vec *origin, t_vec *dir, float t_min)
 {
	t_vec	oc;

	oc = vec_sub(origin, &(cylinder->pos));
    float	a = (dir->x * dir->x) + (dir->y * dir->y);
    float	b = 2 * ((dir->x * oc.x) + (dir->y * oc.y));
    float	c = (oc.x * oc.x)+ (oc.y * oc.y)
		- ((cylinder->diameter / 2) * (cylinder->diameter /2));
    float	discriminant = (b * b) - (4 * a * c);
    
    if (discriminant < 0)
        return (INFINITY);
    float	t1 = (-b - sqrt(discriminant)) / (2 * a);
    float	t2 = (-b + sqrt(discriminant)) / (2 * a);
	if (!(t_min < t1 && t_min < t2))
	{
		// return (INFINITY);
		return (check_capped_part(t1, t2, origin, dir, cylinder));
	}
	float z1 = origin->z + t1 * dir->z;
	float z2 = origin->z + t2 * dir->z;
	if ((t2 < t_min || t1 < t2) && z1 > cylinder->pos.z && z1 < cylinder->pos.z + cylinder->height)
		return (t1);
	if (z2 > cylinder->pos.z && z2 < cylinder->pos.z + cylinder->height)
		return (t2);
	return (INFINITY);

}
*/