/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_tracing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 11:37:30 by ayassin           #+#    #+#             */
/*   Updated: 2023/01/17 16:56:27 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

float	hit_cylinder(
		t_cylinder *cylinder, t_vec *origin, t_vec *dir, float t_min)
{
	t_cylinder_tracing_kit	c;

	init_ct_kit(&c, dir, origin, cylinder);
	c.qudratic = solve_cylinder_quadratic(cylinder, &c);
	if (c.qudratic.x < t_min && c.qudratic.y < t_min)
		return (INFINITY);
	c.temp_vec = vec_scalar_mult(dir, c.qudratic.x);
	c.limit_1 = vec_add(&c.origin_to_cylinder, &c.temp_vec);
	c.h_limit_1 = vec_dot(&cylinder->vec_height, &c.limit_1);
	c.temp_vec = vec_scalar_mult(c.dir, c.qudratic.y);
	c.limit_2 = vec_add(&c.origin_to_cylinder, &c.temp_vec);
	c.h_limit_2 = vec_dot(&cylinder->vec_height, &c.limit_2);
	if (c.qudratic.x < t_min && c.h_limit_2
		> 0 && c.h_limit_2 < cylinder->height)
		return (c.qudratic.y);
	if ((c.qudratic.y < t_min || c.qudratic.x < c.qudratic.y)
		&& c.h_limit_1 > 0 && c.h_limit_1 < cylinder->height)
		return (c.qudratic.x);
	if (c.h_limit_2 > 0 && c.h_limit_2 < cylinder->height)
		return (c.qudratic.y);
	return (INFINITY);
}

void	init_ct_kit(
	t_cylinder_tracing_kit *c, t_vec *dir, t_vec *origin, t_cylinder *cylinder)
{
	c->dir = dir;
	c->origin_to_cylinder = vec_sub(origin, &(cylinder->pos));
	normalize(&cylinder->vec_height);
	c->height_by_direction = vec_dot(&cylinder->vec_height, dir);
	cylinder->in_cylinder
		= vec_dot(&cylinder->vec_height, &(c->origin_to_cylinder));
}

t_vec	solve_cylinder_quadratic(
		t_cylinder *cylinder, t_cylinder_tracing_kit *cy)
{
	float	a;
	float	b;
	float	c;

	a = vec_dot(cy->dir, cy->dir)
		- cy->height_by_direction * cy->height_by_direction;
	b = 2 * (vec_dot(cy->dir, &cy->origin_to_cylinder)
			- cy->height_by_direction * cylinder->in_cylinder);
	c = vec_dot(&cy->origin_to_cylinder, &cy->origin_to_cylinder)
		- cylinder->in_cylinder * cylinder->in_cylinder
		- cylinder->radius_square;
	return (qudratic_equation(a, b, c));
}

t_vec	trace_cylinder(t_vec *dir, float t_min, t_scene *scene)
{
	t_trace_cylinder_kit	t;

	init_trace_cylinder_kit(&t);
	while (t.i < scene->n_cylinders)
	{
		t.temp_t = hit_cylinder(
				&(scene->cylinder[t.i]), &scene->camera.view_point, dir, t_min);
		if (t.temp_t < t.closest_t)
		{
			t.closest_t = t.temp_t;
			t.closest_cylinder = &(scene->cylinder[t.i]);
		}
		t.i++;
	}
	t.color = 0x000000;
	if (t.closest_cylinder != NULL)
	{
		t.m = compute_cylinder_color
			(scene, dir, t.closest_cylinder, t.closest_t);
		t.cyl_color
			= vec_multiply_two_vectors(&(t.closest_cylinder->color), &t.m);
		t.color = vec_to_color(t.cyl_color);
	}
	fill_single_vector(&t.result, t.closest_t, t.color, 0);
	return (t.result);
}

void	init_trace_cylinder_kit(t_trace_cylinder_kit *t)
{
	ft_bzero((void *)t, sizeof(t_trace_cylinder_kit));
	t->i = 0;
	t->closest_t = INFINITY;
	t->closest_cylinder = NULL;
}
