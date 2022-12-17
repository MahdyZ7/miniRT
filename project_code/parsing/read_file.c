/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 01:58:04 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/18 02:07:54 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

//parse everything and fill the scene here inshalla
int	init_scene(
		char **argv, t_scene *scene, t_win *win)
{
	scene->win = win;
	(void)argv;
	return (0);
}
