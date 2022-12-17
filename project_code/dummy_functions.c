/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dummy_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 12:07:17 by ayassin           #+#    #+#             */
/*   Updated: 2022/12/17 12:09:40 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	put_ellipse(t_img *img, int width, int hight)
{
	double	i;
	double	j;
	int		color;

	color = (255 << 16) + (127 << 8) + (0);
	i = 0;
	while (i < width)
	{
		j = 0;
		while (j < hight)
		{
			if (pow((i - width / 2.0), 2) / pow(width / 4.0, 2) + pow((j - hight / 2.0), 2) / pow(hight / 4.0, 2) <= 1.0)
			// if (pow((i - width / 2), 2) + pow((j - hight / 2), 2) <= pow(((width+ hight) / 8), 2))
				pixel_put(img, i , j, color);
			++j;
		}
		++i;
	}
}

void	put_serpenski(t_img *img, int width, int hight)
{
	int		i;
	int		j;
	char	*line;
	char	*temp;
	int		color;

	color = 0xff8000;
	line = (char *)malloc(sizeof(*line) * width);
	i = 0;
	while (i < width)
		line[i++] = 0;
	line[width / 2] = 1;
	ft_strlen(line);
	j = 0;
	while (j < hight)
	{
		i = 1;
		temp = (char *)malloc(sizeof(temp) * width);
		temp[0] = 0;
		temp [width - 1] = 0;
		while (i < width - 1)
		{
			if (line[i] == 1)
				pixel_put(img, i, j, color);
			temp[i] = line[i - 1] ^ line[i + 1];
			++i;
		}
		free(line);
		line = temp;
		++color;
		if (color >= 16777215)
			color = (255 << 16) + (127 << 8) + (0);
		++j;
	}
	free(line);
}

void	put_ellipse2(t_img *img, int x, int y)
{
	double	i;
	double	j;
	int		color;
	int		raduis;

	raduis = 1;
	color = (255 << 16) + (127 << 8) + (0);
	i = x - raduis;
	while (i < img->width && i <= x + raduis)
	{
		j = y - raduis;
		while (j < img->hight && j <+ y + raduis)
		{
			if (pow((i - x), 2) + pow((j - y), 2) <= pow(raduis, 2))
				pixel_put(img, i, j, color);
			++j;
		}
		++i;
	}
}

void	put_border(t_img *img)
{
	double	i;
	double	j;
	int		color;

	color = (30 << 16) + (180 << 8) + (255);
	i = 0;
	j = 0;
	while (i < img->width)
	{
		pixel_put(img, i, 0, color);
		pixel_put(img, i, (img->hight) - 1, color);
		i++;
	}
	while (j < img->hight)
	{
		pixel_put(img, 0, j, color);
		pixel_put(img, (img->width) - 1, j, color);
		j++;
	}
}