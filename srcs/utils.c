/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atable <atable@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 23:18:12 by atable            #+#    #+#             */
/*   Updated: 2020/10/09 00:20:20 by atable           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	abs_angel(float angel)
{
	if (angel < 0)
		angel += 2 * M_PI;
	if (angel > 2 * (float)M_PI)
		angel -= 2 * M_PI;
	return (angel);
}

int		get_color(t_wind data, int x, int y)
{
	return (*(unsigned int*)(data.adr + (y * data.ll +
		x * (data.bpp / 8))));
}

void	my_mlx_pixel_put(t_wind *data, int x, int y, int color)
{
	char	*dst;

	dst = data->adr + (y * data->ll + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

int		init_path_null(t_vars *cub)
{
	cub->north.img = NULL;
	cub->north.adr = NULL;
	cub->south.img = NULL;
	cub->south.adr = NULL;
	cub->east.img = NULL;
	cub->east.adr = NULL;
	cub->west.img = NULL;
	cub->west.adr = NULL;
	cub->sprite.img = NULL;
	cub->sprite.adr = NULL;
	cub->wind.adr = 0;
	cub->wind.img = 0;
	return (1);
}

float	*find_dist(t_vars *cub, float *hor, float *vert)
{
	if (hor[4] < 0)
	{
		if (vert[2] > 0)
			cub->side = 3;
		else
			cub->side = 4;
		return (vert);
	}
	if (vert[4] < 0 || hor[4] < vert[4])
	{
		if (hor[3] > 0)
			cub->side = 2;
		else
			cub->side = 1;
		return (hor);
	}
	if (vert[2] > 0)
		cub->side = 3;
	else
		cub->side = 4;
	return (vert);     
}