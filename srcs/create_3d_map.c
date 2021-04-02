/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_3d_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atable <atable@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 22:47:39 by atable            #+#    #+#             */
/*   Updated: 2020/10/08 22:59:39 by atable           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	draw_3d_map(t_vars *cub)
{
	int		i;
	float	ray_dir;
	float	dalpha;
	float	start[2];

	i = 0;
	cub->dir_rad = cub->pos.dir * M_PI / 180;
	dalpha = cub->fov_rad / cub->wind.resol.w;
	ray_dir = cub->dir_rad - cub->fov_rad / 2;
	start[0] = cub->pos.x * cub->cub_side + cub->player_size;
	start[1] = cub->pos.y * cub->cub_side + cub->player_size;
	while (i < cub->wind.resol.w)
	{
		draw_ray(cub, abs_angel(ray_dir), i, start);
		ray_dir = ray_dir + dalpha;
		i++;
	}
	draw_sprite(cub, start);
	if (cub->save == 0)
		mlx_put_image_to_window(cub->mlx, cub->win, cub->wind.img, 0, 0);
	else
		return (make_bmp(cub));
	return (0);
}

int	sprites(char **map, t_vars *cub)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	cub->sprites = 0;
	while (map[i] != NULL)
	{
		while (map[i][j] != '\0')
		{
			if (map[i][j] == '2')
				cub->sprites += 1;
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

int	find_sprite(char **map, t_vars *cub)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	if (!(cub->spr = (t_spr *)malloc(sizeof(t_spr) * cub->sprites)))
		return (0);
	while (map[i] != NULL)
	{
		while (map[i][j] != '\0')
		{
			if (map[i][j] == '2')
			{
				cub->spr[k].y = i * cub->cub_side + cub->player_size;
				cub->spr[k].x = j * cub->cub_side + cub->player_size;
				k++;
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

int	make_wind(t_data *data)
{
	t_vars	cub;

	cub.mlx = NULL;
	cub.mlx = mlx_init();
	if (initial_cub(data, &cub) == -1)
	{
		free_struct(data);
		free(cub.mlx);
		return (-1);
	}
	sprites(cub.map, &cub);
	find_sprite(cub.map, &cub);
	cub.save = data->save;
	cub.win = NULL;
	if (data->save == 0)
		cub.win = mlx_new_window(cub.mlx, cub.wind.resol.w, cub.wind.resol.h,
		"CUB");
	cub.wind.img = mlx_new_image(cub.mlx, cub.wind.resol.w, cub.wind.resol.h);
	cub.wind.adr = mlx_get_data_addr(cub.wind.img, &cub.wind.bpp, &cub.wind.ll,
		&cub.wind.endian);
	draw_3d_map(&cub);
	mlx_hook(cub.win, 2, 1L << 0, keyboard, &cub);
	mlx_hook(cub.win, 17, 1L << 17, del_win, &cub);
	mlx_loop(cub.mlx);
	return (0);
}
