/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atable <atable@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 18:21:54 by atable            #+#    #+#             */
/*   Updated: 2020/10/08 23:40:36 by atable           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			sort_dist(t_vars *cub)
{
	int		i;
	int		j;
	t_spr	tmp;

	i = 0;
	j = 0;
	while (i < cub->sprites - 1)
	{
		while (j < (cub->sprites - i - 1))
		{
			if (cub->spr[j].dist < cub->spr[j + 1].dist)
			{
				tmp = cub->spr[j];
				cub->spr[j] = cub->spr[j + 1];
				cub->spr[j + 1] = tmp;
			}
			j++;
		}
		j = 0;
		i++;
	}
}

static int	sprite_color2(t_vars *cub, int *offset, float sprite_size, int *pos)
{
	int color;
	int i;
	int j;

	i = (float)cub->sprite.resol.w / sprite_size * pos[0];
	j = (float)cub->sprite.resol.h / sprite_size * pos[1];
	color = get_color(cub->sprite, i, j);
	if (color > 0)
		my_mlx_pixel_put(&cub->wind, offset[0] + pos[0],
		offset[1] + pos[1], color);
	return (0);
}

static int	sprite_color(t_vars *cub, float size, int *offset, float dist)
{
	int pos[2];
	int end_x;
	int end_y;

	pos[0] = (offset[0] < 0) ? ((-1) * offset[0]) : 0;
	end_x = (offset[0] + size >= cub->wind.resol.w) ? 
		(cub->wind.resol.w - offset[0]) : size; 
	end_y = (offset[1] + size >= cub->wind.resol.h) ? 
		(cub->wind.resol.h - offset[1]) : size; 
	while (pos[0] < end_x)
	{
		pos[1] = (offset[1] < 0) ? ((-1) * offset[1]) : 0;
		if (dist < cub->wall_dist[offset[0] + pos[0]])
		{
			while (pos[1] < end_y)
			{
				sprite_color2(cub, offset, size, pos);
				pos[1]++;
			}
		}
		pos[0]++;
	}
	return (0);
}

static int	draw_sprite2(t_vars *cub, float *start, t_spr sprite)
{
	float	sprite_dir;
	float	sprite_size;
	int		offset[2];

	cub->dir_rad = cub->pos.dir * M_PI / 180;
	sprite_dir = atan2((sprite.y - start[1]), (sprite.x - start[0]));
	while (sprite_dir - cub->dir_rad > (float)M_PI)
		sprite_dir -= 2 * (float)M_PI;
	while (sprite_dir - cub->dir_rad < -(float)M_PI)
		sprite_dir += 2 * (float)M_PI;
	sprite_size = cub->wind.resol.h / sprite.dist;
	offset[0] = (sprite_dir - cub->dir_rad) * (cub->wind.resol.w) /
		(cub->fov_rad) + (cub->wind.resol.w) / 2 - sprite_size / 2;
	offset[1] = cub->wind.resol.h / 2 - sprite_size / 2;
	if (offset[0] < cub->wind.resol.w || offset[0] + sprite_size >= 0)
		return (sprite_color(cub, sprite_size, offset, sprite.dist));
}

int			draw_sprite(t_vars *cub, float *start)
{
	int	i;

	i = 0;
	while (i < cub->sprites)
	{
		cub->spr[i].dist = sqrt(pow((start[0] - cub->spr[i].x), 2) +
			pow((start[1] - cub->spr[i].y), 2));
		i++;
	}
	if (cub->sprites > 1)
		sort_dist(cub);
	i = 0;
	while (i < cub->sprites)
	{
		draw_sprite2(cub, start, cub->spr[i]);
		i++;
	}
	return (0);
}