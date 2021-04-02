/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atable <atable@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 15:26:47 by atable            #+#    #+#             */
/*   Updated: 2020/10/10 23:52:17 by atable           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			draw_line(int i, t_vars *cub, int height, float *res)
{
	int	j;
	int	start;
	int	end;
	int	color;

	j = 0;
	start = (cub->wind.resol.h - height) / 2;
	end = (cub->wind.resol.h + height) / 2;
	while (j < cub->wind.resol.h)
	{
		if (j < start)
			my_mlx_pixel_put(&cub->wind, i, j, cub->ceil_color);
		else if (j >= start && j <= end)
		{
			color = texture_color(cub, height, res, j);
			my_mlx_pixel_put(&cub->wind, i, j, color);
		}
		else if (j > end)
			my_mlx_pixel_put(&cub->wind, i, j, cub->floor_color);
		j++;
	}
	return (0);
}

static void	cycle(t_vars *cub, float *start, float ray_dir, float *pos)
{
	if (pos[0] < 0 || (pos[0] / cub->cub_side) > cub->raws ||
		pos[1] < 0 || (pos[1] / cub->cub_side) > cub->lines)
	{
		pos[4] = -1;
		return ;
	}
	while (ft_memchr("02",cub->map[(int)(pos[1] /
		cub->cub_side)][(int)(pos[0] / cub->cub_side)], 2))
	{
		pos[0] += pos[2];
		pos[1] += pos[3];
		if (pos[0] < 0 || pos[0] > (cub->raws * cub->cub_side) ||
			pos[1] < 0 || pos[1] > (cub->lines * cub->cub_side))
		{
			pos[4] = -1;
			return ;
		}
	}
	pos[4] = (start[0] - pos[0]) / cos(ray_dir);
	if (pos[4] < 0)
		pos[4] *= (-1);
}

static void	vertical_trace(t_vars *cub, float *start, float ray_dir, float *vec)
{
	if ((ray_dir > (float)M_PI / 2) && (ray_dir < (float)(3 * M_PI) / 2))
		vec[0] = floor(start[0] / cub->cub_side) * cub->cub_side - 0.0001;
	else if ((ray_dir < (float)M_PI / 2) || (ray_dir > (float)(3 * M_PI) / 2))
		vec[0] = floor(start[0] / cub->cub_side) * cub->cub_side + 2;
	else
	{
		vec[4] = -1;
		return ;
	}
	vec[1] = start[1] - (start[0] - vec[0]) * tanf(ray_dir);
	vec[2] = cub->cub_side;
	if ((ray_dir > (float)M_PI / 2) && (ray_dir < (float)(3 * M_PI) / 2))
		vec[2] *= (-1);
	vec[3] = cub->cub_side * tan(ray_dir);
	if (ray_dir > (float)M_PI)
	{
		if (vec[3] > 0)
			vec[3] *= (-1);
	}
	else
	{
		if (vec[3] < 0)
			vec[3] *= (-1);
	}
	cycle(cub, start, ray_dir, vec);
}

static void	horizont_trace(t_vars *cub, float *start, float ray_dir, float *vec)
{
	if (ray_dir > (float)M_PI)
		vec[1] = floor(start[1] / cub->cub_side) * cub->cub_side - 0.0001;
	else if (ray_dir < (float)M_PI)
		vec[1] = floor(start[1] / cub->cub_side) * cub->cub_side + 2;
	else
	{
		vec[4] = -1;
		return ;
	}
	vec[0] = start[0] - (start[1] - vec[1]) / tanf(ray_dir);
	vec[3] = cub->cub_side;
	if (ray_dir > (float)M_PI)
		vec[3] *= (-1);
	vec[2] = cub->cub_side / tanf(ray_dir);
	if ((ray_dir > (float)M_PI / 2) && (ray_dir < (float)(3 * M_PI / 2)))
	{
		if (vec[2] > 0)
			vec[2] *= (-1);
	}
	else
	{
		if (vec[2] < 0)
			vec[2] *= (-1);
	}
	cycle(cub, start, ray_dir, vec);
}

int			draw_ray(t_vars *cub, float ray_dir, int i, float *start)
{
	int		height;
	float	vert_pos[5];
	float	hor_pos[5];
	float	*res;

	horizont_trace(cub, start, ray_dir, hor_pos);
	vertical_trace(cub, start, ray_dir, vert_pos);
	res = find_dist(cub, hor_pos, vert_pos);
	height = (int)(cub->wind.resol.h / (res[4] * cos(ray_dir - cub->dir_rad)));
	draw_line(i, cub, height, res);
	cub->wall_dist[cub->n] = res[4];
	cub->n += 1;
	return (0);
}