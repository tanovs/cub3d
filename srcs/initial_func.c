/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atable <atable@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 20:10:46 by atable            #+#    #+#             */
/*   Updated: 2020/10/09 10:34:12 by atable           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		initial_data(t_data *data)
{
	data->east_path = NULL;
	data->map = NULL;
	data->north_path = NULL;
	data->south_path = NULL;
	data->sprite_path = NULL;
	data->west_path = NULL;
	data->ceiling.blue = -1;
	data->ceiling.green = -1;
	data->ceiling.red = -1;
	data->floor.red = -1;
	data->floor.green = -1;
	data->floor.blue = -1;
	data->resol.w = -1;
	data->resol.h = -1;
}

static int	screen_size(t_vars *cub, t_res data)
{
	int	size_x;
	int	size_y;

	mlx_get_screen_size(cub->mlx, &size_x, &size_y);
	cub->wind.resol.w = (data.w > size_x) ? size_x : data.w;
	cub->wind.resol.h = (data.h > size_y) ? size_y : data.h;
	return (0);
}

static int	get_address(t_vars *cub)
{
	cub->north.adr = mlx_get_data_addr(cub->north.img, &cub->north.bpp,
		&cub->north.ll, &cub->north.endian);
	cub->south.adr = mlx_get_data_addr(cub->south.img, &cub->south.bpp,
		&cub->south.ll, &cub->south.endian);
	cub->east.adr = mlx_get_data_addr(cub->east.img, &cub->east.bpp,
		&cub->east.ll, &cub->east.endian);
	cub->west.adr = mlx_get_data_addr(cub->west.img, &cub->west.bpp,
		&cub->west.ll, &cub->west.endian);
	cub->sprite.adr = mlx_get_data_addr(cub->sprite.img, &cub->sprite.bpp,
		&cub->sprite.ll, &cub->sprite.endian);
	return (0);
}

static int	initial_image(t_vars *cub, t_data *data)
{
	cub->north.img = mlx_xpm_file_to_image(cub->mlx, data->north_path,
		&cub->north.resol.w, &cub->north.resol.h);
	cub->south.img = mlx_xpm_file_to_image(cub->mlx, data->south_path,
		&cub->south.resol.w, &cub->south.resol.h);
	cub->east.img = mlx_xpm_file_to_image(cub->mlx, data->east_path,
		&cub->east.resol.w, &cub->east.resol.h);
	cub->west.img = mlx_xpm_file_to_image(cub->mlx, data->west_path,
		&cub->west.resol.w, &cub->west.resol.h);
	cub->sprite.img = mlx_xpm_file_to_image(cub->mlx, data->sprite_path,
		&cub->sprite.resol.w, &cub->sprite.resol.h);
	free_path(data);
	if (!cub->north.img || !cub->south.img || !cub->east.img || !cub->west.img ||
		!cub->sprite.img)
		return (destr(cub));
	return (get_address(cub));
}

int			initial_cub(t_data *data, t_vars *cub)
{
	cub->cub_side = 2;
	cub->t_stepx = 2;
	cub->t_stepy = 1;
	cub->map = data->map;
	cub->floor_color = 256 * 256 * data->floor.red + 256 * data->floor.green +
		data->floor.blue;
	cub->ceil_color = 256 * 256 * data->ceiling.red + 256 * data->ceiling.green +
		data->ceiling.blue;
	cub->fov = 66;
	cub->fov_rad = cub->fov * M_PI / 180;
	cub->player_size = cub->cub_side / 2;
	cub->side = 0;
	cub->n = 0;
	if (!(cub->wall_dist = (float *)malloc(sizeof(float) * cub->wind.resol.w)))
		return (-1);
	screen_size(cub, data->resol);
	start_pos(cub, &cub->map);
	init_path_null(cub);
	if (initial_image(cub, data) == -1)
		return (-1);
	return (0);
}