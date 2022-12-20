/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_ratracing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 18:55:05 by ayassin           #+#    #+#             */
/*   Updated: 2022/12/20 19:19:22 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


int trace_ray(int origin, int vx, int vy, int dz, int t_min, int t_max)
{
	int	color;
	int	closest_t;

	return (color);
}

void	basic_raytracing(t_win *win, t_img *img)
{
	int	color;
	int	vx;
	int	vy;
	int	dz;

	color = 0;
	for (int x = 0; x < img->width; x++)
	{
		for (int y = 0; y < img->hight; y++)
		{
			vx = x - img->width / 2; // * 1 / 1 ;
			vy = y - img->hight / 2; // * 1 / 1 ;
			dz = 1;
			color = trace_ray(0, vx, vy, dz, 1, inf);
			// ray = ray_at_pixel(x, y);
			// color = ray_color(ray);
			// write_pixel(x, y, color);
			pixel_put(img, x, y, color);
		}
	}
}