/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atable <atable@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 00:42:22 by tanos             #+#    #+#             */
/*   Updated: 2020/10/09 10:33:19 by atable           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*skip_num(char *line)
{
	line = skip_spaces(line);
	while (ft_memchr("0123456789", *line, 11) && *line != '\0')
		line++;
	return (line);
}

char	*skip_spaces(char *line)
{
	while (*line == ' ' && *line != '\0')
		line++;
	return (line);
}

int destr(t_vars *cub)
{
	if (cub->north.img)
		mlx_destroy_image(cub->mlx, cub->north.img);
	if (cub->south.img)
		mlx_destroy_image(cub->mlx, cub->south.img);
	if (cub->east.img)
		mlx_destroy_image(cub->mlx, cub->east.img);
	if (cub->west.img)
		mlx_destroy_image(cub->mlx, cub->west.img);
	if (cub->sprite.img)
		mlx_destroy_image(cub->mlx, cub->sprite.img);
	return (-1);
}