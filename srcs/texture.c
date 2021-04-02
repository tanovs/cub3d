/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atable <atable@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 22:57:16 by atable            #+#    #+#             */
/*   Updated: 2020/10/09 00:13:51 by atable           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	north_wall(t_vars *cub, int height, int i, float x_coord)
{
	float	x;
	float	y;
	float	step;

	y = i - ((cub->wind.resol.h - height) / 2);
	step = (float)height / (float)cub->t_stepy;
    if (y)
        y = (y - (int)(y / step) * step) * cub->north.resol.h / step;
    x = x_coord - (int)(x_coord / cub->cub_side) * cub->cub_side;
	if (x)
    {
        x = x - (int)(x / ((float)cub->cub_side / cub->t_stepx)) *
			((float)cub->cub_side / cub->t_stepx);
        x = x / ((float)cub->cub_side / cub->t_stepx / cub->north.resol.w);
    }
	return (get_color(cub->north, (int)x, (int)y));
}

static int	south_wall(t_vars *cub, int height, int i, float x_coord)
{
	float	x;
	float	y;
	float	step;

	y = i - ((cub->wind.resol.h - height) / 2);
	step = (float)height / (float)cub->t_stepy;
    if (y)
        y = (y - (int)(y / step) * step) * cub->south.resol.h / step;
    x = x_coord - (int)(x_coord / cub->cub_side) * cub->cub_side;
	if (x)
    {
        x = x - (int)(x / ((float)cub->cub_side / cub->t_stepx)) *
			((float)cub->cub_side / cub->t_stepx);
        x = x / ((float)cub->cub_side / cub->t_stepx / cub->south.resol.w);
    }
	return (get_color(cub->south, (int)x, (int)y));
}

int east_wall(t_vars *cub, int height, int i, float x_coord)
{
	float	x;
	float	y;
	float	step;

	y = i - ((cub->wind.resol.h - height) / 2);
	step = (float)height / (float)cub->t_stepy;
    if (y)
        y = (y - (int)(y / step) * step) * cub->east.resol.h / step;
    x = x_coord - (int)(x_coord / cub->cub_side) * cub->cub_side;
	if (x)
    {
        x = x - (int)(x / ((float)cub->cub_side / cub->t_stepx)) *
			((float)cub->cub_side / cub->t_stepx);
        x = x / ((float)cub->cub_side / cub->t_stepx / cub->east.resol.w);
    }
	return (get_color(cub->east, (int)x, (int)y));
}

static int	west_wall(t_vars *cub, int height, int i, float x_coord)
{
	float	x;
	float	y;
	float	step;

	y = i - ((cub->wind.resol.h - height) / 2);
	step = (float)height / (float)cub->t_stepy;
    if (y)
        y = (y - (int)(y / step) * step) * cub->west.resol.h / step;
    x = x_coord - (int)(x_coord / cub->cub_side) * cub->cub_side;
	if (x)
    {
        x = x - (int)(x / ((float)cub->cub_side / cub->t_stepx)) *
			((float)cub->cub_side / cub->t_stepx);
        x = x / ((float)cub->cub_side / cub->t_stepx / cub->west.resol.w);
    }
	return (get_color(cub->west, (int)x, (int)y));
}

int			texture_color(t_vars *cub, int height, float *res, int i)
{
	if (cub->side == 1)
		return (north_wall(cub, height, i, res[0]));
	else if (cub->side == 2)
        return (south_wall(cub, height, i, res[0]));
	else if (cub->side == 3)
        return (east_wall(cub, height, i, res[1]));
    return (west_wall(cub, height, i, res[1]));
}