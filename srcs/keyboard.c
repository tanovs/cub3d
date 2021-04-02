/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atable <atable@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 12:23:10 by atable            #+#    #+#             */
/*   Updated: 2020/10/09 00:00:10 by atable           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	go_back_forward(int key, t_vars *cub)
{
	float	pos[2];
	float	step;

	step = 0.1;
	cub->dir_rad = cub->pos.dir * M_PI / 180;
	if (key == 0xff52 || key == 0x77 || key == 126 || key == 13)
	{
		pos[0] = cub->pos.x + step * cos(cub->dir_rad);
		pos[1] = cub->pos.y + step * sin(cub->dir_rad);
	}
	else if (key == 0xff54 || key == 0x73 || key == 125 || key == 1)
	{
		pos[0] = cub->pos.x - step * cos(cub->dir_rad);
		pos[1] = cub->pos.y - step * sin(cub->dir_rad);
	}
	if (cub->map[(int)rint(pos[1])][(int)rint(pos[0])] != '0' &&
		cub->map[(int)rint(pos[1])][(int)rint(pos[0])] != '2')
		return (0);
	cub->pos.x = pos[0];
	cub->pos.y = pos[1];
	draw_3d_map(cub);
	return (0);
}

static int	turn_left_right(int key, t_vars *cub)
{
	float	angel;
	float	step;

	angel = cub->pos.dir * M_PI / 180;
	step = M_PI / 100;
	if (key == 0xff53 || key == 124)
		angel = abs_angel(angel + step);     
	else
		angel = abs_angel(angel - step);
	cub->pos.dir = angel * 180 / M_PI;
	draw_3d_map(cub);
	return (0);
}

int			del_win(t_vars *cub)
{
	free_array(cub->map);
	free(cub->spr);
	free(cub->wall_dist);
	mlx_destroy_image(cub->mlx, cub->north.img);
	mlx_destroy_image(cub->mlx, cub->south.img);
	mlx_destroy_image(cub->mlx, cub->east.img);
	mlx_destroy_image(cub->mlx, cub->west.img);
	mlx_destroy_image(cub->mlx, cub->sprite.img);
	mlx_destroy_image(cub->mlx, cub->wind.img);
	if (cub->win != NULL)
		mlx_destroy_window(cub->mlx, cub->win);
	free(cub->mlx);
	exit(1);
}

static int	strafe_left_right(int key, t_vars *cub)
{
	float	pos[2];
	float	step;

	step = 0.1;
	cub->dir_rad = cub->pos.dir * M_PI / 180;
	if (key == 0x61 || key == 0)
	{
		pos[0] = cub->pos.x + step * cos(cub->dir_rad - M_PI / 2);
		pos[1] = cub->pos.y + step * sin(cub->dir_rad - M_PI / 2);
	}
	else
	{
		pos[0] = cub->pos.x + step * cos(cub->dir_rad + M_PI / 2);
		pos[1] = cub->pos.y + step * sin(cub->dir_rad + M_PI / 2);
	}
	if (cub->map[(int)rint(pos[1])][(int)rint(pos[0])] != '0' &&
		cub->map[(int)rint(pos[1])][(int)rint(pos[0])] != '2')
		return (0);
	cub->pos.x = pos[0];
	cub->pos.y = pos[1];
	draw_3d_map(cub);
	return (0);
}

int			keyboard(int key, t_vars *cub)
{
	cub->n = 0;
	if (key == 0xff52 || key == 0x77 || key == 126 || key == 13 ||
	key == 0xff54 || key == 0x73 || key == 125 || key == 1)
		return (go_back_forward(key, cub));
	if (key == 0xff53 || key == 0xff51 || key == 124 || key == 123)
		return (turn_left_right(key, cub));
	if (key == 0x61 || key == 0x64)
		return (strafe_left_right(key, cub));        
	if (key == 65307 || key == 53)
		return (del_win(cub));
	return (0);
}