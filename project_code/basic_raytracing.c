/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_raytracing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 18:55:05 by ayassin           #+#    #+#             */
/*   Updated: 2023/01/05 21:11:41 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	basic_raytracing(t_img *img)
{
	t_ray_trace_kit	r;

	init_ray_trace_kit(&r, img);
	while (r.x < WIN_WIDTH)
	{
		r.y = 0;
		while (r.y < WIN_HIGHT)
		{
			r.new_x = (2 * ((r.x + 0.5) * r.invWidth) - 1)
				* r.angle * r.aspectratio;
			r.new_y = (1 - 2 * ((r.y + 0.5) * r.invHeight)) * r.angle;
			vec_init(&r.dir, r.new_x, r. new_y,
				img->scene->camera.view_point.z + 1);
			// r.color = trace_sphere(&r.dir, 1, img->scene);
			r.color = trace_plane(&r.dir, 1, img->scene);
			// r.color = trace_cylinder(&r.dir, 1, img->scene);
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
	r->invWidth = 1 / (float)WIN_WIDTH;
	r->invHeight = 1 / (float)WIN_HIGHT;
	r->aspectratio = (float)WIN_WIDTH / (float)WIN_HIGHT;
	r->angle = tan(M_PI * 0.5 * img->scene->camera.view_field / 180.);
	r->color = 0;
}
