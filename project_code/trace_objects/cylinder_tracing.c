/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_tracing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 11:37:30 by ayassin           #+#    #+#             */
/*   Updated: 2023/01/13 19:54:18 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

float	hit_cylinder(t_cylinder *cylinder, t_vec *origin, t_vec *dir, float t_min)
{
	t_cylinder_tracing_kit	c;

	init_ct_kit(&c, dir, origin, cylinder);
	c.qudratic = solve_cylinder_quadratic(cylinder, &c);
	if (c.qudratic.x < t_min && c.qudratic.y < t_min)
		return INFINITY;
	c.temp_vec = vec_scalar_mult(dir, c.qudratic.x);
	c.limit_1 = vec_add(&c.origin_to_cylinder, &c.temp_vec);
	c.h_limit_1 = vec_dot(&cylinder->vec_height, &c.limit_1);
	c.temp_vec = vec_scalar_mult(c.dir, c.qudratic.y);
	c.limit_2 = vec_add(&c.origin_to_cylinder, &c.temp_vec);
	c.h_limit_2 = vec_dot(&cylinder->vec_height, &c.limit_2);
	if (c.qudratic.x < t_min && c.h_limit_2 > 0 && c.h_limit_2 < cylinder->height)
		return c.qudratic.y;
	if ((c.qudratic.y < t_min || c.qudratic.x < c.qudratic.y) && c.h_limit_1 > 0 && c.h_limit_1 < cylinder->height)
		return c.qudratic.x;
	if (c.h_limit_2 > 0 && c.h_limit_2 < cylinder->height)
		return (c.qudratic.y);
	return (INFINITY);
}

void	init_ct_kit(t_cylinder_tracing_kit *c, t_vec *dir, t_vec *origin, t_cylinder *cylinder)
{
	c->dir = dir;
	c->origin_to_cylinder = vec_sub(origin, &(cylinder->pos));
	normalize(&cylinder->vec_height);
	c->height_by_direction = vec_dot(&cylinder->vec_height, dir);
	cylinder->in_cylinder = vec_dot(&cylinder->vec_height, &(c->origin_to_cylinder));

}

t_vec	solve_cylinder_quadratic(t_cylinder *cylinder, t_cylinder_tracing_kit *cy)
{
	float	a;
	float	b;
	float	c;

	a =  vec_dot(cy->dir, cy->dir) - cy->height_by_direction * cy->height_by_direction;
	b = 2 * (vec_dot(cy->dir, &cy->origin_to_cylinder) - cy->height_by_direction * cylinder->in_cylinder);
	c = vec_dot(&cy->origin_to_cylinder, &cy->origin_to_cylinder)
		- cylinder->in_cylinder * cylinder->in_cylinder - cylinder->radius_square;
	return(qudratic_equation(a, b, c));
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
		temp_t = hit_cylinder(&(scene->cylinder[i]), &scene->camera.view_point, dir, t_min);
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
	}
	fill_single_vector(&result, closest_t, color, 0);
	return (result);
}

/* old code
float	hit_cylinder(t_cylinder *cylinder, t_vec *origin, t_vec *dir, float t_min)
 {
	t_vec	oc;

	oc = vec_sub(origin, &(cylinder->pos));
    float	a = (dir->x * dir->x) + (dir->y * dir->y);
    float	b = 2 * ((dir->x * ocy->x) + (dir->y * oc.y));
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