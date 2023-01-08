/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_raytracing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 18:55:05 by ayassin           #+#    #+#             */
/*   Updated: 2023/01/08 18:41:35 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "miniRT.h"

void	basic_raytracing(t_img *img)
{
	t_ray_trace_kit	r;
	t_vec			plane_result;
	t_vec			sphere_result;
	t_vec			cylinder_result;

	init_ray_trace_kit(&r, img);
	while (r.x < WIN_WIDTH)
	{
		r.y = 0;
		while (r.y < WIN_HIGHT)
		{
			r.new_x = (2 * ((r.x + 0.5) * r.invwidth) - 1)
				* r.angle * r.aspectratio;
			r.new_y = (1 - 2 * ((r.y + 0.5) * r.invheight)) * r.angle;
			vec_init(&r.dir, r.new_x, r. new_y, 1);
			r.dir = dir_with_camera_orientation(&r.dir, r.new_x, r. new_y, img->scene);
			plane_result = trace_plane(&r.dir, img->scene);
			sphere_result = trace_sphere(&r.dir, img->scene->camera.view_point.z + 1, img->scene);
			cylinder_result = trace_cylinder(&r.dir, img->scene->camera.view_point.z + 1, img->scene);
			if (plane_result.x < sphere_result.x && plane_result.x < cylinder_result.x)
				r.color = plane_result.y;
			else if (sphere_result.x < plane_result.x && sphere_result.x < cylinder_result.x)
				r.color = sphere_result.y;
			else
				r.color = cylinder_result.y;
			pixel_put(img->scene->win->img, r.x, r.y, r.color);
			++r.y;
		}
		r.x++;
	}
}

void	init_ray_trace_kit(t_ray_trace_kit *r, t_img *img)
{
	r->x = 0;
	r->y = 0;
	r->invwidth = 1 / (float)WIN_WIDTH;
	r->invheight = 1 / (float)WIN_HIGHT;
	r->aspectratio = (float)WIN_WIDTH / (float)WIN_HIGHT;
	r->angle = tan(M_PI * 0.5 * img->scene->camera.view_field / 180.);
	r->color = 0;
}
